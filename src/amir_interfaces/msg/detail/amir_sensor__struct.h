// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from amir_interfaces:msg/AmirSensor.idl
// generated code does not contain a copyright notice

#ifndef AMIR_INTERFACES__MSG__DETAIL__AMIR_SENSOR__STRUCT_H_
#define AMIR_INTERFACES__MSG__DETAIL__AMIR_SENSOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AmirSensor in the package amir_interfaces.
typedef struct amir_interfaces__msg__AmirSensor
{
  float angle[6];
  float vel[6];
} amir_interfaces__msg__AmirSensor;

// Struct for a sequence of amir_interfaces__msg__AmirSensor.
typedef struct amir_interfaces__msg__AmirSensor__Sequence
{
  amir_interfaces__msg__AmirSensor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} amir_interfaces__msg__AmirSensor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AMIR_INTERFACES__MSG__DETAIL__AMIR_SENSOR__STRUCT_H_
