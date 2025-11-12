#include <gz/sim/Entity.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/sim/EventManager.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/System.hh>
#include <gz/sim/components/ExternalWorldWrenchCmd.hh>
#include <gz/sim/components/Model.hh>
#include <gz/plugin/Register.hh>
#include <gz/math/Vector3.hh>
#include <gz/msgs/wrench.pb.h>

#include <rclcpp/rclcpp.hpp>
#include <custom_vtol_plugin/msg/motor_commands.hpp>

#include <array>
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

namespace custom_vtol_plugin
{

class MotorControllerPlugin
  : public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPostUpdate
{
public:
  MotorControllerPlugin() = default;

  ~MotorControllerPlugin() override
  {
    std::cout << "[motor_controller_plugin] ~dtor: stopping executor...\n";
    running_ = false;
    if (exec_thread_.joinable()) {
      exec_thread_.join();
    }
    if (rclcpp::ok()) {
      rclcpp::shutdown();
    }
    std::cout << "[motor_controller_plugin] ~dtor: done.\n";
  }

  void Configure(const gz::sim::Entity &_entity,
                 const std::shared_ptr<const sdf::Element> & /*_sdf*/,
                 gz::sim::EntityComponentManager &_ecm,
                 gz::sim::EventManager & /*_eventMgr*/) override
  {
    std::cout << "[motor_controller_plugin] Configure() begin\n";

    // Bind to model (prefer the provided entity; fallback by name)
    if (_ecm.EntityHasComponentType(_entity, gz::sim::components::Model::typeId)) {
      model_ = gz::sim::Model(_entity);
      std::cout << "[motor_controller_plugin] Bound to provided entity: "
                << model_.Name(_ecm) << "\n";
    } else {
      gz::sim::Entity chosen = gz::sim::kNullEntity;
      _ecm.Each<gz::sim::components::Model>(
        [&](const gz::sim::Entity &e, const gz::sim::components::Model *) -> bool
        {
          gz::sim::Model m(e);
          auto name = m.Name(_ecm);
          if (name == "standard_vtol") { chosen = e; return false; }
          if (chosen == gz::sim::kNullEntity) chosen = e;
          return true;
        });
      if (chosen != gz::sim::kNullEntity) {
        model_ = gz::sim::Model(chosen);
        std::cout << "[motor_controller_plugin] Bound to model: "
                  << model_.Name(_ecm) << "\n";
      } else {
        std::cout << "[motor_controller_plugin] WARNING: No model found. Plugin will run ROS node only.\n";
      }
    }

    // ---- ROS 2 global init , node and executor
    std::cout << "[motor_controller_plugin] Initializing ROS2...\n";
    if (!rclcpp::ok()) {
      try {
        rclcpp::init(0, nullptr);
        std::cout << "[motor_controller_plugin] rclcpp::init OK\n";
      } catch (const std::exception &e) {
        std::cerr << "[motor_controller_plugin] rclcpp::init FAILED: " << e.what() << "\n";
        return;
      }
    }

    try {
      ros_node_ = std::make_shared<rclcpp::Node>("motor_controller_plugin");
      std::cout << "[motor_controller_plugin] Node created: " << ros_node_->get_name() << "\n";
    } catch (const std::exception &e) {
      std::cerr << "[motor_controller_plugin] Node creation FAILED: " << e.what() << "\n";
      return;
    }

    auto qos = rclcpp::SensorDataQoS();

    //  ROS2 Subscriber node
    try {
      sub_ = ros_node_->create_subscription<custom_vtol_plugin::msg::MotorCommands>(
        "/motor_vtol/motor_commands", qos,
        [this](custom_vtol_plugin::msg::MotorCommands::SharedPtr msg)
        {
          std::lock_guard<std::mutex> lock(mutex_);
          for (size_t i = 0; i < commands_.size() && i < msg->motor_values.size(); ++i) {
            commands_[i] = msg->motor_values[i];
          }
          std::cout << "[motor_controller_plugin] Received motor command: ";
          for (auto val : msg->motor_values) std::cout << val << " ";
          std::cout << std::endl;
        });
      std::cout << "[motor_controller_plugin] Subscriber created on /motor_vtol/motor_commands\n";
    } catch (const std::exception &e) {
      std::cerr << "[motor_controller_plugin] Subscription FAILED: " << e.what() << "\n";
      return;
    }

    // Start executor on a background thread
    try {
      executor_ = std::make_shared<rclcpp::executors::SingleThreadedExecutor>();
      executor_->add_node(ros_node_);
      running_ = true;
      exec_thread_ = std::thread([this]()
      {
        std::cout << "[motor_controller_plugin] executor thread: spinning\n";
        while (running_) {
          executor_->spin_some();
          std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
        std::cout << "[motor_controller_plugin] executor thread: exit\n";
      });
    } catch (const std::exception &e) {
      std::cerr << "[motor_controller_plugin] Executor setup FAILED: " << e.what() << "\n";
      return;
    }

    // Find rotor links
    if (model_.Entity() != gz::sim::kNullEntity) {
      std::vector<std::string> rotor_names = {"rotor_0", "rotor_1", "rotor_2", "rotor_3", "rotor_puller"};
      for (const auto &name : rotor_names) {
        auto link_entity = model_.LinkByName(_ecm, name);
        if (link_entity == gz::sim::kNullEntity) {
          std::cout << "[motor_controller_plugin] WARN: rotor link '" << name << "' not found\n";
        } else {
          rotor_entities_.push_back(link_entity);
          std::cout << "[motor_controller_plugin] Found rotor link: " << name << "\n";
        }
      }
    }

    std::cout << "[motor_controller_plugin] Configure() done. ROS node up.\n";
  }

  // --------------------------------------------------------------------------
  // PostUpdate: apply thrust each simulation step
  // --------------------------------------------------------------------------
  void PostUpdate(const gz::sim::UpdateInfo &_info,
                  const gz::sim::EntityComponentManager &_ecm) override
  {
    if (_info.paused || rotor_entities_.empty())
      return;

    std::array<int16_t, 5> cmd_copy;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      cmd_copy = commands_;
    }

    auto &ecm = const_cast<gz::sim::EntityComponentManager &>(_ecm);

    for (size_t i = 0; i < rotor_entities_.size() && i < cmd_copy.size(); ++i) {
      const auto entity = rotor_entities_[i];
      const double delta = std::max(0.0, static_cast<double>(cmd_copy[i]) - 1000.0);
      const double thrust = delta * K_THRUST_GAIN;

      gz::math::Vector3d force(0, 0, thrust);
      double yaw_dir = (i % 2 == 0) ? 1.0 : -1.0;
      gz::math::Vector3d torque(0, 0, thrust * K_YAW_TORQUE_GAIN * yaw_dir);

      auto wrench_comp = ecm.Component<gz::sim::components::ExternalWorldWrenchCmd>(entity);
      if (!wrench_comp) {
        ecm.CreateComponent(entity, gz::sim::components::ExternalWorldWrenchCmd{});
        wrench_comp = ecm.Component<gz::sim::components::ExternalWorldWrenchCmd>(entity);
      }

      if (wrench_comp) {
        gz::msgs::Wrench wrench_msg;
        wrench_msg.mutable_force()->set_x(force.X());
        wrench_msg.mutable_force()->set_y(force.Y());
        wrench_msg.mutable_force()->set_z(force.Z());
        wrench_msg.mutable_torque()->set_x(torque.X());
        wrench_msg.mutable_torque()->set_y(torque.Y());
        wrench_msg.mutable_torque()->set_z(torque.Z());
        ecm.SetComponentData<gz::sim::components::ExternalWorldWrenchCmd>(entity, wrench_msg);
      }
    }
  }

private:
  gz::sim::Model model_{gz::sim::kNullEntity};
  std::vector<gz::sim::Entity> rotor_entities_;

  std::array<int16_t, 5> commands_{{1500, 1500, 1500, 1500, 0}};
  std::mutex mutex_;

  // ROS 2
  std::shared_ptr<rclcpp::Node> ros_node_;
  rclcpp::Subscription<custom_vtol_plugin::msg::MotorCommands>::SharedPtr sub_;
  std::shared_ptr<rclcpp::executors::SingleThreadedExecutor> executor_;
  std::thread exec_thread_;
  std::atomic<bool> running_{false};

  // Gains
  const double K_THRUST_GAIN = 0.06; //Has to be tuned !!!
  const double K_YAW_TORQUE_GAIN = 0.001; ////Has to be tuned !!!
};

} // namespace custom_vtol_plugin

GZ_ADD_PLUGIN(custom_vtol_plugin::MotorControllerPlugin,
              gz::sim::System,
              custom_vtol_plugin::MotorControllerPlugin::ISystemConfigure,
              custom_vtol_plugin::MotorControllerPlugin::ISystemPostUpdate)
