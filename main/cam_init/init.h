#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"

esp_err_t jpg_stream_httpd_handler(httpd_req_t *req);
static camera_config_t camera_config;
esp_err_t camera_init();
esp_err_t camera_capture();