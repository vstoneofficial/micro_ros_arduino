#ifndef MICRO_ROS_ARDUINO_JAZZY_H
#define MICRO_ROS_ARDUINO_JAZZY_H

// Include this before any rcl/rclc/message headers to select the Jazzy library.
#if defined(MICRO_ROS_ARDUINO_DISTRO_HUMBLE)
#error "micro_ros_arduino: cannot mix Humble and Jazzy in one sketch"
#endif

#include "micro_ros_arduino.h"

#endif  // MICRO_ROS_ARDUINO_JAZZY_H
