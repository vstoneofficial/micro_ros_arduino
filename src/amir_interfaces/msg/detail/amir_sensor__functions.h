// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from amir_interfaces:msg/AmirSensor.idl
// generated code does not contain a copyright notice

#ifndef AMIR_INTERFACES__MSG__DETAIL__AMIR_SENSOR__FUNCTIONS_H_
#define AMIR_INTERFACES__MSG__DETAIL__AMIR_SENSOR__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "amir_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "amir_interfaces/msg/detail/amir_sensor__struct.h"

/// Initialize msg/AmirSensor message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * amir_interfaces__msg__AmirSensor
 * )) before or use
 * amir_interfaces__msg__AmirSensor__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
bool
amir_interfaces__msg__AmirSensor__init(amir_interfaces__msg__AmirSensor * msg);

/// Finalize msg/AmirSensor message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
void
amir_interfaces__msg__AmirSensor__fini(amir_interfaces__msg__AmirSensor * msg);

/// Create msg/AmirSensor message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * amir_interfaces__msg__AmirSensor__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
amir_interfaces__msg__AmirSensor *
amir_interfaces__msg__AmirSensor__create();

/// Destroy msg/AmirSensor message.
/**
 * It calls
 * amir_interfaces__msg__AmirSensor__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
void
amir_interfaces__msg__AmirSensor__destroy(amir_interfaces__msg__AmirSensor * msg);

/// Check for msg/AmirSensor message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
bool
amir_interfaces__msg__AmirSensor__are_equal(const amir_interfaces__msg__AmirSensor * lhs, const amir_interfaces__msg__AmirSensor * rhs);

/// Copy a msg/AmirSensor message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
bool
amir_interfaces__msg__AmirSensor__copy(
  const amir_interfaces__msg__AmirSensor * input,
  amir_interfaces__msg__AmirSensor * output);

/// Initialize array of msg/AmirSensor messages.
/**
 * It allocates the memory for the number of elements and calls
 * amir_interfaces__msg__AmirSensor__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
bool
amir_interfaces__msg__AmirSensor__Sequence__init(amir_interfaces__msg__AmirSensor__Sequence * array, size_t size);

/// Finalize array of msg/AmirSensor messages.
/**
 * It calls
 * amir_interfaces__msg__AmirSensor__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
void
amir_interfaces__msg__AmirSensor__Sequence__fini(amir_interfaces__msg__AmirSensor__Sequence * array);

/// Create array of msg/AmirSensor messages.
/**
 * It allocates the memory for the array and calls
 * amir_interfaces__msg__AmirSensor__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
amir_interfaces__msg__AmirSensor__Sequence *
amir_interfaces__msg__AmirSensor__Sequence__create(size_t size);

/// Destroy array of msg/AmirSensor messages.
/**
 * It calls
 * amir_interfaces__msg__AmirSensor__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
void
amir_interfaces__msg__AmirSensor__Sequence__destroy(amir_interfaces__msg__AmirSensor__Sequence * array);

/// Check for msg/AmirSensor message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
bool
amir_interfaces__msg__AmirSensor__Sequence__are_equal(const amir_interfaces__msg__AmirSensor__Sequence * lhs, const amir_interfaces__msg__AmirSensor__Sequence * rhs);

/// Copy an array of msg/AmirSensor messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_amir_interfaces
bool
amir_interfaces__msg__AmirSensor__Sequence__copy(
  const amir_interfaces__msg__AmirSensor__Sequence * input,
  amir_interfaces__msg__AmirSensor__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AMIR_INTERFACES__MSG__DETAIL__AMIR_SENSOR__FUNCTIONS_H_
