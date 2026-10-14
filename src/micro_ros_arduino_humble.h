#ifndef MICRO_ROS_ARDUINO_HUMBLE_H
#define MICRO_ROS_ARDUINO_HUMBLE_H

// Include this before any rcl/rclc/message headers to select the Humble library.
#if defined(MICRO_ROS_ARDUINO_DISTRO_JAZZY)
#error "micro_ros_arduino: cannot mix Humble and Jazzy in one sketch"
#endif

#include "micro_ros_arduino.h"

#endif  // MICRO_ROS_ARDUINO_HUMBLE_H
