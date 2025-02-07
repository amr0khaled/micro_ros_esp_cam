#include <stddef.h>
void error_loop();

#define RCCHECK(fn, module){\
  rcl_ret_t temp = fn;\
  char* tag = "MICRO-ROS: "; \
  do {\
    if (temp != RCL_RET_OK)\
      {error_loop(tag, module);}\
  } while(0);\
}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_ = fn; if((temp_ != RCL_RET_OK)){}}

#define CHECK(fn, module){esp_err_t temp = fn; if (temp != ESP_OK) {error_loop(TAG, module);}}