# Encoder snapshot for Vstone research and development rovers.
# header.stamp is ROS-synchronized time at completion of ALL encoder reads in
# one acquisition cycle, not publication time. Sequential reads do not imply
# that the encoders were sampled at exactly the same instant.
# Do not publish before ROS time synchronization or if ANY read in this cycle
# fails. Never remove failed elements or substitute values from a previous cycle.
# header.frame_id is the empty string in the initial deployment.
std_msgs/Header header

# Raw signed 32-bit motor encoder values, in count. No conversion to angle or
# distance, sign inversion, or wrap correction. A 32-bit counter can wrap and
# a motor restart can reset it; consumers must account for these discontinuities.
# The encoder count is the length of this unbounded sequence. Firmware manages
# the supported count per model; the interface has no fixed length or maximum 8.
# Index-to-wheel/motor mapping is fixed per model and shared in sender/PC
# configuration and documentation. Current two-wheel Megarover: [0] left, [1] right.
# Four-/eight-wheel and other mappings are defined when each model is implemented.
# Keep sequence order and length unchanged during normal operation of a model.
int32[] counts
