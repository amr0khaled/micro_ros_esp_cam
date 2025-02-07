# ESP-CAM
For streaming esp32 AI Thinker Camera through ROS using Micro ROS.
Camera sensor currently using is OV2640.

# Installiation
That installiation is from my own experience maybe i will get it wrong.

## 1. Setup ESP-IDF
### 1.0 (Optional) Install ESP-IDF as Docker Image
Install Docker & Dev Containers Extensions for Vscode.
Build Docker image from `.devcontainer` through Dev Containers extension
### 1.1. Clone ESP-IDF
Specify a location for esp-idf and run this command.
```bash
git clone --recursive https://github.com/espressif/esp-idf.git
```
### 1.2. (Recommended) Install ESP-IDF extension in Visual Studio Code
I recommend to install ESP-IDF extension to make it easier in building, flashing and monitoring esp32 from Vscode directly,
and configure esp-idf location to the extension and go through all configuration process and all is done :).

### 1.3.1 (Optional but Advanced) Export ESP-IDF Location as environment variable
Export esp-idf path as environment variable.
And replace `TO_ESP_IDF_Location` with it correct location.
```bash
# Linux
echo "export IDF_PATH='{TO_ESP_IDF_Location}'"
```
For Windows you can copy it's location and set it in Setting in Environment variables.
### 1.3.2 Enabling ESP-IDF to work with
To enable esp-idf in terminal.
```bash
# Linux
. $IDF_PATH/export.sh
# Windows
. $IDF_PATH/export.ps1
# OR
. $IDF_PATH/export.bat
```
## 2. Setup project
You can fork it or clone it or tell me to contribute.
When cloning run this to install all sub-modules.
```bash
git clone --recursive https://github.com/amr0khaled/micro_ros_esp_cam.git
```
# Project Structure
```
├── .devcontainer/ -> Contain the setting to Vscode and to install ESP-IDF as Docker Image
├── CMakeLists.txt  -> Links ESP-IDF components to the project
└── main
    ├── CMakeLists.txt  -> Import your new C files and require your needed to work libraries
    ├── main.c  -> The main poin
    ├── idf_component.yml -> To import your external components
    ├── network/init.c -> Initilizing Wifi connection (Configure the static ip to your preferences)
    └── cam_init/init.c -> Initilizing Camera to stream JPEG captured images
```

# ESP32 Firmware Configuration
After installing esp-idf you can configure esp32 firmware using `idf.py`
First enable esp-idf and run this command line to view configuration menu
```bash
# Enable ESP-IDF
. $IDF_PATH/export.sh
# View Configuration Menu
idf.py menuconfig
```

# To Build and Flash using terminal
These is the steps
But first change directory to root of the project
```bash
cd micro_ros_esp_cam

# Build
idf.py build

# Flash (And you can set the Baud using -b option but i recommend to not do it)
idf.py flash -p <PORT>

# Monitoring
idf.py monitor -p <PORT>
```
