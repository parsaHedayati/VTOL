#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

#include <gz/transport/Node.hh>
#include <gz/msgs/double_v.pb.h>

class CustomBridge : public rclcpp::Node {
public:
  CustomBridge() : Node("custom_bridge") {
    // Declare parameter with default topic
    this->declare_parameter<std::string>(
      "motor_topic", "/model/standard_vtol/command/motor_speed");

    // Get parameter value
    std::string topic = this->get_parameter("motor_topic").as_string();

    
    pub_ = gz_node_.Advertise<gz::msgs::Double_V>(topic);

    // Subscribe to ROS motor command
    sub_ = this->create_subscription<std_msgs::msg::Float64MultiArray>(
      "/ros_motor_command", 10,
      std::bind(&CustomBridge::callback, this, std::placeholders::_1));

    RCLCPP_INFO(this->get_logger(), "Publishing to Gazebo topic: %s", topic.c_str());
  }

private:
  void callback(const std_msgs::msg::Float64MultiArray::SharedPtr msg) {
    gz::msgs::Double_V gz_msg;
    for (auto val : msg->data) {
      gz_msg.add_data(val);
    }
    pub_.Publish(gz_msg);
    RCLCPP_INFO(this->get_logger(), "Bridged %zu values to Gazebo", msg->data.size());
  }

  gz::transport::Node gz_node_;
  gz::transport::Node::Publisher pub_;
  rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr sub_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<CustomBridge>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
