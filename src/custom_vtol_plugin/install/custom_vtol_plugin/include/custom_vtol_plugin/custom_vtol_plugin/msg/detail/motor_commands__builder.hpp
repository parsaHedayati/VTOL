// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_vtol_plugin:msg/MotorCommands.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__BUILDER_HPP_
#define CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_vtol_plugin/msg/detail/motor_commands__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_vtol_plugin
{

namespace msg
{

namespace builder
{

class Init_MotorCommands_motor_values
{
public:
  Init_MotorCommands_motor_values()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_vtol_plugin::msg::MotorCommands motor_values(::custom_vtol_plugin::msg::MotorCommands::_motor_values_type arg)
  {
    msg_.motor_values = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_vtol_plugin::msg::MotorCommands msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_vtol_plugin::msg::MotorCommands>()
{
  return custom_vtol_plugin::msg::builder::Init_MotorCommands_motor_values();
}

}  // namespace custom_vtol_plugin

#endif  // CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__BUILDER_HPP_
