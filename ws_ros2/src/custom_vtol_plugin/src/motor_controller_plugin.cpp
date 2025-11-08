#include <gz/common/Console.hh>                     // Fixed
#include <ignition/plugin/Register.hh>              // Fixed (GZ_ADD_PLUGIN → IGNITION_ADD_PLUGIN)
#include <gz/sim/components/ExternalWorldWrench.hh> // Fixed
#include <gz/sim/components/Link.hh>
#include <gz/sim/EntityComponentManager.hh>
#include <gz/sim/Model.hh>
#include <gz/sim/System.hh>
#include <gz/sim/Util.hh>

// Standard C++ and ROS includes
#include <gazebo_ros/node.hpp>
#include <rclcpp/rclcpp.hpp>

// Include the generated custom message header
#include "custom_vtol_plugin/msg/motor_commands.hpp"

namespace custom_vtol_plugin
{
using MotorCommands = custom_vtol_plugin::msg::MotorCommands;

class MotorControllerSystem :
  public gz::sim::System,
  public gz::sim::ISystemConfigure,
  public gz::sim::ISystemPostUpdate
{
private:
  gazebo_ros::Node::SharedPtr ros_node_{nullptr};
  rclcpp::Subscription<MotorCommands>::SharedPtr sub_;
  std::array<int16_t, 4> latest_commands_ = {1000, 1000, 1000, 1000};

  std::vector<gz::sim::Entity> rotor_entities_;
  std::vector<double> yaw_directions_ = {1.0, 1.0, -1.0, -1.0};

  const double K_THRUST_GAIN = 0.05;
  const double K_YAW_TORQUE_GAIN = 0.001;

public:
  void Configure(const gz::sim::Entity& _entity,
                 const std::shared_ptr<const sdf::Element>& _sdf,
                 gz::sim::EntityComponentManager& _ecm,
                 gz::sim::EventManager& /*_eventMgr*/) override
  {
    this->ros_node_ = gazebo_ros::Node::Get(_sdf);  // Preferred way

    gz::sim::Model model(_entity);
    if (!model.Valid(_ecm)) {
      RCLCPP_ERROR(this->ros_node_->get_logger(), "Invalid model entity.");
      return;
    }

    std::vector<std::string> rotor_names = {"rotor_0", "rotor_1", "rotor_2", "rotor_3"};
    for (const auto& name : rotor_names) {
      auto entity = model.LinkByName(_ecm, name);
      if (entity != gz::sim::kInvalidEntity) {
        rotor_entities_.push_back(entity);
        RCLCPP_INFO(this->ros_node_->get_logger(), "Found rotor: %s", name.c_str());
      } else {
        RCLCPP_ERROR(this->ros_node_->get_logger(), "Failed to find rotor: %s", name.c_str());
      }
    }

    this->sub_ = this->ros_node_->create_subscription<MotorCommands>(
        "/motor_commands", 10,
        [this](const MotorCommands::SharedPtr msg) {
          for (int i = 0; i < 4; ++i)
            this->latest_commands_[i] = msg->motor_values[i];
        });

    RCLCPP_INFO(this->ros_node_->get_logger(), "Subscribed to /motor_commands.");
  }

  void PostUpdate(const gz::sim::UpdateInfo& _info,
                  const gz::sim::EntityComponentManager& _ecm) override
  {
    if (_info.paused || rotor_entities_.size() != 4) return;

    for (size_t i = 0; i < 4; ++i) {
      double motor_delta = std::max(0.0, static_cast<double>(latest_commands_[i]) - 1000.0);
      double thrust = motor_delta * K_THRUST_GAIN;
      double yaw_torque = thrust * K_YAW_TORQUE_GAIN * yaw_directions_[i];

      gz::math::Vector3d force(0, 0, thrust);
      gz::math::Vector3d torque(0, 0, yaw_torque);

      auto wrench = _ecm.Component<gz::sim::components::ExternalWorldWrench>(rotor_entities_[i]);
      if (!wrench) {
        auto& ecm = const_cast<gz::sim::EntityComponentManager&>(_ecm);
        ecm.CreateComponent(rotor_entities_[i], gz::sim::components::ExternalWorldWrench{});
        wrench = ecm.Component<gz::sim::components::ExternalWorldWrench>(rotor_entities_[i]);
      }
      wrench->Data().Set(force, torque);
    }
  }
};

// Modern plugin registration for Ignition Gazebo 6+
IGNITION_ADD_PLUGIN(
    custom_vtol_plugin::MotorControllerSystem,
    gz::sim::System,
    custom_vtol_plugin::MotorControllerSystem::ISystemConfigure,
    custom_vtol_plugin::MotorControllerSystem::ISystemPostUpdate
)
}  // namespace custom_vtol_plugin