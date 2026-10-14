// Receives AMIR commands and publishes synthetic zero sensor values.
// This message smoke test does not drive motors or read robot hardware.
#include <micro_ros_arduino_humble.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <amir_interfaces/msg/amir_cmd.h>
#include <amir_interfaces/msg/amir_sensor.h>

rclc_support_t support;
rcl_node_t node;
rcl_publisher_t publisher;
rcl_subscription_t subscription;
rcl_timer_t timer;
rclc_executor_t executor;
amir_interfaces__msg__AmirCmd command;
amir_interfaces__msg__AmirSensor sensor;

void check(rcl_ret_t result) {
  if (result != RCL_RET_OK) {
    while (true) {
      delay(100);
    }
  }
}

void command_callback(const void * message) {
  // Deserialization into command is exercised by the executor.
  (void)message;
}

void timer_callback(rcl_timer_t * source, int64_t last_call_time) {
  (void)last_call_time;
  if (source != nullptr) {
    check(rcl_publish(&publisher, &sensor, nullptr));
  }
}

void setup() {
  set_microros_transports();  // Serial: 921600 bps.
  delay(2000);
  if (!amir_interfaces__msg__AmirCmd__init(&command) ||
      !amir_interfaces__msg__AmirSensor__init(&sensor)) {
    check(RCL_RET_ERROR);
  }
  rcl_allocator_t allocator = rcl_get_default_allocator();
  check(rclc_support_init(&support, 0, nullptr, &allocator));
  check(rclc_node_init_default(&node, "amir_smoke", "", &support));
  check(rclc_publisher_init_default(
    &publisher, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(amir_interfaces, msg, AmirSensor),
    "amir_smoke/sensor"));
  check(rclc_subscription_init_default(
    &subscription, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(amir_interfaces, msg, AmirCmd),
    "amir_smoke/cmd"));
  check(rclc_timer_init_default(
    &timer, &support, RCL_MS_TO_NS(1000), timer_callback));
  check(rclc_executor_init(&executor, &support.context, 2, &allocator));
  check(rclc_executor_add_subscription(
    &executor, &subscription, &command, command_callback, ON_NEW_DATA));
  check(rclc_executor_add_timer(&executor, &timer));
}

void loop() {
  check(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10)));
  delay(10);
}
