// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from custom_vtol_plugin:msg/MotorCommands.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__TRAITS_HPP_
#define CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "custom_vtol_plugin/msg/detail/motor_commands__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace custom_vtol_plugin
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorCommands & msg,
  std::ostream & out)
{
  out << "{";
  // member: motor_values
  {
    if (msg.motor_values.size() == 0) {
      out << "motor_values: []";
    } else {
      out << "motor_values: [";
      size_t pending_items = msg.motor_values.size();
      for (auto item : msg.motor_values) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorCommands & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: motor_values
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.motor_values.size() == 0) {
      out << "motor_values: []\n";
    } else {
      out << "motor_values:\n";
      for (auto item : msg.motor_values) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorCommands & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace custom_vtol_plugin

namespace rosidl_generator_traits
{

[[deprecated("use custom_vtol_plugin::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_vtol_plugin::msg::MotorCommands & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_vtol_plugin::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_vtol_plugin::msg::to_yaml() instead")]]
inline std::string to_yaml(const custom_vtol_plugin::msg::MotorCommands & msg)
{
  return custom_vtol_plugin::msg::to_yaml(msg);
}

template<>
inline const char * data_type<custom_vtol_plugin::msg::MotorCommands>()
{
  return "custom_vtol_plugin::msg::MotorCommands";
}

template<>
inline const char * name<custom_vtol_plugin::msg::MotorCommands>()
{
  return "custom_vtol_plugin/msg/MotorCommands";
}

template<>
struct has_fixed_size<custom_vtol_plugin::msg::MotorCommands>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<custom_vtol_plugin::msg::MotorCommands>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<custom_vtol_plugin::msg::MotorCommands>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__TRAITS_HPP_
