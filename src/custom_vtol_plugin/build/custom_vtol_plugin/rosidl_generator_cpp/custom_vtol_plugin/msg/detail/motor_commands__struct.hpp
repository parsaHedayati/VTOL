// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_vtol_plugin:msg/MotorCommands.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_HPP_
#define CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_vtol_plugin__msg__MotorCommands __attribute__((deprecated))
#else
# define DEPRECATED__custom_vtol_plugin__msg__MotorCommands __declspec(deprecated)
#endif

namespace custom_vtol_plugin
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorCommands_
{
  using Type = MotorCommands_<ContainerAllocator>;

  explicit MotorCommands_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int16_t, 4>::iterator, int16_t>(this->motor_values.begin(), this->motor_values.end(), 0);
    }
  }

  explicit MotorCommands_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : motor_values(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int16_t, 4>::iterator, int16_t>(this->motor_values.begin(), this->motor_values.end(), 0);
    }
  }

  // field types and members
  using _motor_values_type =
    std::array<int16_t, 4>;
  _motor_values_type motor_values;

  // setters for named parameter idiom
  Type & set__motor_values(
    const std::array<int16_t, 4> & _arg)
  {
    this->motor_values = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_vtol_plugin__msg__MotorCommands
    std::shared_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_vtol_plugin__msg__MotorCommands
    std::shared_ptr<custom_vtol_plugin::msg::MotorCommands_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorCommands_ & other) const
  {
    if (this->motor_values != other.motor_values) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorCommands_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorCommands_

// alias to use template instance with default allocator
using MotorCommands =
  custom_vtol_plugin::msg::MotorCommands_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_vtol_plugin

#endif  // CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_HPP_
