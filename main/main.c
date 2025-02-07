#define CAMERA_MODEL_AI_THINKER 
#include <stdio.h>
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
#include "main.h"
#include "network/init.h"
#define TAG "MAIN"

void error_loop();
void initilization();


rclc_executor_t  executor;
rcl_allocator_t  allocator;
rclc_support_t  support;
rcl_publisher_t  publisher;
rcl_node_t node;
std_msgs__msg__UInt8__Sequence * frame_buf;

static char *ssid = "POCO";
static char *passwd = "12345777";

void app_main(void) {
  ESP_LOGI(TAG, "Start Initilization");
  initilization();
  ESP_LOGI(TAG, "Setting WIFI");
  wifi_init(ssid, passwd);
}


void initilization() {
  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator), "Init RCL Supprt");
  RCCHECK(rclc_node_init_default(&node, "cam_stream_pub", "smart_city",&support), "Init Node");
  RCCHECK(rclc_publisher_init_default(
    &publisher, 
    &node,
     ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, UInt8),
     "camera_stream"
     ), "Init Publisher");
  RCCHECK(rclc_executor_init(&executor, &support.context, 5, &allocator), "Init Executor");
}
// Function Error Handling 
void error_loop(char*tag, char * module) {
  gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);
  while(1) {
    ESP_LOGE(TAG, "%s->ERROR: %s", tag, module);
    gpio_set_level(GPIO_NUM_4, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
    ESP_LOGE(TAG, "%s->ERROR: %s", tag, module);
    gpio_set_level(GPIO_NUM_4, 1);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}