#define CAMERA_MODEL_AI_THINKER 
#include <stdio.h>
#include "micro_ros_arduino.h"
#include <rclc/node.h>
#include <rclc/publisher.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rclc/types.h>
#include <rcl/allocator.h>
#include <std_msgs/msg/u_int8.h>
#include <std_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h>
#include "esp_camera.h"
#include "camera_pins.h"
#include "esp_log.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "esp_wifi.h"
#include "cam_init/init.h"
#define CHECK(fn){rcl_ret_t temp = fn; if (temp != RCL_RET_OK) {error_loop();}}
#define SOFTCHECK(fn) { rcl_ret_t temp_ = fn; if((temp_ != RCL_RET_OK)){}}
void error_loop();
void initilization();

// 


rclc_executor_t  executor;
rcl_allocator_t  allocator;
rclc_support_t  support;
rcl_publisher_t  publisher;
rcl_node_t node;
std_msgs__msg__UInt8__Sequence * frame_buf;


void app_main(void) {
  // initilization();

}


void initilization() {
  set_microros_transports();
  allocator = rcl_get_default_allocator();
  rclc_support_init(&support, 0, NULL, &allocator);
  rclc_node_init_default(&node, "cam_stream_pub", "smart_city",&support);
  rclc_publisher_init_default(
    &publisher, 
    &node,
     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
     "camera_stream"
     );
  rclc_executor_init(&executor, &support.context, 10, &allocator);
}
// Function Error Handling 
void error_loop() {
  while(1) {
    digitalWrite(2, 1);
    delay(100);
    digitalWrite(2, 0);
    delay(100);
  }
}