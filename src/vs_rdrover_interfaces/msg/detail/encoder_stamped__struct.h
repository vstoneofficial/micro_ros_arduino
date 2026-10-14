// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vs_rdrover_interfaces:msg/EncoderStamped.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "vs_rdrover_interfaces/msg/encoder_stamped.h"


#ifndef VS_RDROVER_INTERFACES__MSG__DETAIL__ENCODER_STAMPED__STRUCT_H_
#define VS_RDROVER_INTERFACES__MSG__DETAIL__ENCODER_STAMPED__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'counts'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/EncoderStamped in the package vs_rdrover_interfaces.
/**
  * Encoder snapshot for Vstone research and development rovers.
  * header.stamp is ROS-synchronized time at completion of ALL encoder reads in
  * one acquisition cycle, not publication time. Sequential reads do not imply
  * that the encoders were sampled at exactly the same instant.
  * Do not publish before ROS time synchronization or if ANY read in this cycle
  * fails. Never remove failed elements or substitute values from a previous cycle.
  * header.frame_id is the empty string in the initial deployment.
 */
typedef struct vs_rdrover_interfaces__msg__EncoderStamped
{
  std_msgs__msg__Header header;
  /// Raw signed 32-bit motor encoder values, in count. No conversion to angle or
  /// distance, sign inversion, or wrap correction. A 32-bit counter can wrap and
  /// a motor restart can reset it; consumers must account for these discontinuities.
  /// The encoder count is the length of this unbounded sequence. Firmware manages
  /// the supported count per model; the interface has no fixed length or maximum 8.
  /// Index-to-wheel/motor mapping is fixed per model and shared in sender/PC
  /// configuration and documentation. Current two-wheel Megarover: [0] left, [1] right.
  /// Four-/eight-wheel and other mappings are defined when each model is implemented.
  /// Keep sequence order and length unchanged during normal operation of a model.
  rosidl_runtime_c__int32__Sequence counts;
} vs_rdrover_interfaces__msg__EncoderStamped;

// Struct for a sequence of vs_rdrover_interfaces__msg__EncoderStamped.
typedef struct vs_rdrover_interfaces__msg__EncoderStamped__Sequence
{
  vs_rdrover_interfaces__msg__EncoderStamped * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vs_rdrover_interfaces__msg__EncoderStamped__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VS_RDROVER_INTERFACES__MSG__DETAIL__ENCODER_STAMPED__STRUCT_H_
