// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_vtol_plugin:msg/MotorCommands.idl
// generated code does not contain a copyright notice
#include "custom_vtol_plugin/msg/detail/motor_commands__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
custom_vtol_plugin__msg__MotorCommands__init(custom_vtol_plugin__msg__MotorCommands * msg)
{
  if (!msg) {
    return false;
  }
  // motor_values
  return true;
}

void
custom_vtol_plugin__msg__MotorCommands__fini(custom_vtol_plugin__msg__MotorCommands * msg)
{
  if (!msg) {
    return;
  }
  // motor_values
}

bool
custom_vtol_plugin__msg__MotorCommands__are_equal(const custom_vtol_plugin__msg__MotorCommands * lhs, const custom_vtol_plugin__msg__MotorCommands * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // motor_values
  for (size_t i = 0; i < 5; ++i) {
    if (lhs->motor_values[i] != rhs->motor_values[i]) {
      return false;
    }
  }
  return true;
}

bool
custom_vtol_plugin__msg__MotorCommands__copy(
  const custom_vtol_plugin__msg__MotorCommands * input,
  custom_vtol_plugin__msg__MotorCommands * output)
{
  if (!input || !output) {
    return false;
  }
  // motor_values
  for (size_t i = 0; i < 5; ++i) {
    output->motor_values[i] = input->motor_values[i];
  }
  return true;
}

custom_vtol_plugin__msg__MotorCommands *
custom_vtol_plugin__msg__MotorCommands__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_vtol_plugin__msg__MotorCommands * msg = (custom_vtol_plugin__msg__MotorCommands *)allocator.allocate(sizeof(custom_vtol_plugin__msg__MotorCommands), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_vtol_plugin__msg__MotorCommands));
  bool success = custom_vtol_plugin__msg__MotorCommands__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_vtol_plugin__msg__MotorCommands__destroy(custom_vtol_plugin__msg__MotorCommands * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_vtol_plugin__msg__MotorCommands__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_vtol_plugin__msg__MotorCommands__Sequence__init(custom_vtol_plugin__msg__MotorCommands__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_vtol_plugin__msg__MotorCommands * data = NULL;

  if (size) {
    data = (custom_vtol_plugin__msg__MotorCommands *)allocator.zero_allocate(size, sizeof(custom_vtol_plugin__msg__MotorCommands), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_vtol_plugin__msg__MotorCommands__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_vtol_plugin__msg__MotorCommands__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_vtol_plugin__msg__MotorCommands__Sequence__fini(custom_vtol_plugin__msg__MotorCommands__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_vtol_plugin__msg__MotorCommands__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_vtol_plugin__msg__MotorCommands__Sequence *
custom_vtol_plugin__msg__MotorCommands__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_vtol_plugin__msg__MotorCommands__Sequence * array = (custom_vtol_plugin__msg__MotorCommands__Sequence *)allocator.allocate(sizeof(custom_vtol_plugin__msg__MotorCommands__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_vtol_plugin__msg__MotorCommands__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_vtol_plugin__msg__MotorCommands__Sequence__destroy(custom_vtol_plugin__msg__MotorCommands__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_vtol_plugin__msg__MotorCommands__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_vtol_plugin__msg__MotorCommands__Sequence__are_equal(const custom_vtol_plugin__msg__MotorCommands__Sequence * lhs, const custom_vtol_plugin__msg__MotorCommands__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_vtol_plugin__msg__MotorCommands__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_vtol_plugin__msg__MotorCommands__Sequence__copy(
  const custom_vtol_plugin__msg__MotorCommands__Sequence * input,
  custom_vtol_plugin__msg__MotorCommands__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_vtol_plugin__msg__MotorCommands);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_vtol_plugin__msg__MotorCommands * data =
      (custom_vtol_plugin__msg__MotorCommands *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_vtol_plugin__msg__MotorCommands__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_vtol_plugin__msg__MotorCommands__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_vtol_plugin__msg__MotorCommands__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
