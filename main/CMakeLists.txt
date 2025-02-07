idf_component_register(SRCS
  "main.c"
  "cam_init/init.c"
  "network/init.c"
  REQUIRES esp_timer
  REQUIRES esp_http_server
  REQUIRES micro_ros
  INCLUDE_DIRS "."
)
