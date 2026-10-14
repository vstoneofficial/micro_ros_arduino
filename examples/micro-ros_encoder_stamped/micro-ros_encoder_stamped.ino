// Synthetic encoder data only: no motor control or hardware acquisition.
#include <micro_ros_arduino_jazzy.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>
#include <vs_rdrover_interfaces/msg/encoder_stamped.h>
#include <stdint.h>

#ifndef ENCODER_COUNT
#define ENCODER_COUNT 2
#endif
static_assert(ENCODER_COUNT > 0, "Choose the encoder count for this model");

rclc_support_t support;
rcl_node_t node;
rcl_publisher_t publisher;
rcl_timer_t timer;
rclc_executor_t executor;
// The executor retains a pointer to its allocator, so keep it alive after setup.
rcl_allocator_t allocator;
vs_rdrover_interfaces__msg__EncoderStamped message = {};
int32_t counts_storage[ENCODER_COUNT] = {};
char frame_id_storage[1] = {'\0'};

void check(rcl_ret_t result) {
  if (result != RCL_RET_OK) {
    while (true) {
      delay(100);
    }
  }
}

// Fill every element for this cycle. A hardware implementation must return
// false on ANY failed read; never compact the array or reuse a previous value.
bool read_synthetic_counts(int32_t * counts, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    counts[i] = (i % 2 == 0) ? 123 : -456;
  }
  return true;
}

void timer_callback(rcl_timer_t * source, int64_t last_call_time) {
  (void)last_call_time;
  if (source == nullptr || !rmw_uros_epoch_synchronized() ||
      message.counts.size != ENCODER_COUNT ||
      message.counts.size > message.counts.capacity) {
    return;
  }
  if (!read_synthetic_counts(message.counts.data, message.counts.size)) {
    return;
  }
  // Timestamp immediately after completing ALL reads, not at publication.
  const int64_t completed_ns = rmw_uros_epoch_nanos();
  if (!rmw_uros_epoch_synchronized() || completed_ns <= 0 ||
      completed_ns / 1000000000LL > INT32_MAX) {
    return;
  }
  message.header.stamp.sec = static_cast<int32_t>(completed_ns / 1000000000LL);
  message.header.stamp.nanosec = static_cast<uint32_t>(completed_ns % 1000000000LL);
  // Best effort telemetry: a failed send drops this sample without retrying it.
  const rcl_ret_t result = rcl_publish(&publisher, &message, nullptr);
  (void)result;
}

void setup() {
  set_microros_transports();  // Serial: 921600 bps.
  delay(2000);

  // Static storage is valid for the whole program. Do not call generated
  // __init/__fini/__destroy or free() on this manually backed message.
  message.counts.data = counts_storage;
  message.counts.size = ENCODER_COUNT;
  message.counts.capacity = sizeof(counts_storage) / sizeof(counts_storage[0]);
  message.header.frame_id.data = frame_id_storage;
  message.header.frame_id.size = 0;
  message.header.frame_id.capacity = sizeof(frame_id_storage);

  allocator = rcl_get_default_allocator();
  check(rclc_support_init(&support, 0, nullptr, &allocator));
  check(rclc_node_init_default(&node, "encoder_stamped_smoke", "", &support));
  check(rclc_publisher_init_best_effort(
    &publisher, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(vs_rdrover_interfaces, msg, EncoderStamped),
    "rover_encoder_stamped"));

  // Initial synchronization happens before the periodic executor is started.
  while (rmw_uros_sync_session(1000) != RMW_RET_OK ||
         !rmw_uros_epoch_synchronized()) {
    delay(100);
  }
  check(rclc_timer_init_default2(
    &timer, &support, RCL_MS_TO_NS(20), timer_callback, true));
  check(rclc_executor_init(&executor, &support.context, 1, &allocator));
  check(rclc_executor_add_timer(&executor, &timer));
  // Allocate the wait set now, instead of on the first periodic spin.
  check(rclc_executor_prepare(&executor));
}

void loop() {
  check(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(1)));
  delay(1);
}
