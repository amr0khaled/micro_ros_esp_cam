#ifndef __CAM_INIT__
#define __CAM_INIT__
#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"

static camera_config_t camera_config;
esp_err_t jpg_stream_httpd_handler(httpd_req_t *req);
esp_err_t camera_init();
esp_err_t camera_capture();
esp_err_t process_image(size_t width, size_t height, pixformat_t format, uint8_t * buf, size_t len, std_msgs__msg__UInt8__Sequence * msg);
#endif