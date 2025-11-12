// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_vtol_plugin:msg/MotorCommands.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_H_
#define CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/MotorCommands in the package custom_vtol_plugin.
/**
  * Motor commands for 4 vertical lift rotors.
 */
typedef struct custom_vtol_plugin__msg__MotorCommands
{
  /// Range is 1000 (min thrust) to 2000 (max thrust).
  /// Order [0, 1, 2, 3] maps to [RR, FL, RL, FR]
  int16_t motor_values[4];
} custom_vtol_plugin__msg__MotorCommands;

// Struct for a sequence of custom_vtol_plugin__msg__MotorCommands.
typedef struct custom_vtol_plugin__msg__MotorCommands__Sequence
{
  custom_vtol_plugin__msg__MotorCommands * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_vtol_plugin__msg__MotorCommands__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_VTOL_PLUGIN__MSG__DETAIL__MOTOR_COMMANDS__STRUCT_H_
