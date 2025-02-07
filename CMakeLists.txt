# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include_directories($ENV{IDF_PATH}/components/**)

include(/home/amr0khaled/microros_ws/firmware/toolchain/esp-idf/tools/cmake/project.cmake)
add_compile_options(-DBOARD_HAS_PSRAM=1)
project(esp-cam)
