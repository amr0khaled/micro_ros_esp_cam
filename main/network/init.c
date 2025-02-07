#include "main.h"
#include <stdio.h> //for basic printf commands
#include <string.h> //for handling strings
#include <freertos/FreeRTOS.h> //for delay,mutexs,semphrs rtos operations
#include <esp_system.h> //esp_init funtions esp_err_t 
#include <esp_wifi.h> //esp_wifi_init functions and wifi operations
#include <esp_log.h> //for showing logs
#include <esp_event.h> //for wifi event
#include <nvs_flash.h> //non volatile storage
#include <lwip/err.h> //light weight ip packets error handling
#include <lwip/sys.h> //system applications for light weight ip apps
#include "init.h"
#define TAG "WIFI"
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT      BIT1
#define MAX_RETRY 10
#define IP_ADDR "192.168.236.100"
#define MASK "255.255.255.0"
#define GATEAWAY "192.168.236.1"

static int retry_count = 0;

static esp_netif_t *netif = NULL;
static EventGroupHandle_t wifi_event_group;

static void wifi_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        if (retry_count < MAX_RETRY) {
            esp_wifi_connect();
            retry_count++;
            ESP_LOGI(TAG, "Retrying connection... (%d/%d)", retry_count, MAX_RETRY);
        } else {
            xEventGroupSetBits(wifi_event_group, WIFI_FAIL_BIT);
            ESP_LOGE(TAG, "Failed to connect to Wi-Fi.");
        }
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t *event = (ip_event_got_ip_t *) event_data;
        ESP_LOGI(TAG, "Connected! Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        retry_count = 0;
        xEventGroupSetBits(wifi_event_group, WIFI_CONNECTED_BIT);
    }
}
void wifi_connect(char * ssid, char * passwd) {
  wifi_event_group = xEventGroupCreate();
  ESP_LOGI(TAG, "Setting esp_netif_init");
  CHECK(esp_netif_init(), "ESP netif init");
  ESP_LOGI(TAG, "Setting esp_event_loop");
  CHECK(esp_event_loop_create_default(), "ESP event loop");
  ESP_LOGI(TAG, "Setting esp_netif_create_default_wifi_sta");
  netif = esp_netif_create_default_wifi_sta();
  CHECK(esp_netif_dhcpc_stop(netif), "Disable DHCP to set a static ip");

  esp_netif_ip_info_t ip_info;
  ip_info.ip.addr = esp_ip4addr_aton(IP_ADDR);
  ip_info.gw.addr = esp_ip4addr_aton(GATEAWAY);
  ip_info.netmask.addr = esp_ip4addr_aton(MASK);

  CHECK(esp_netif_set_ip_info(netif, &ip_info), "Setting static ip");

  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_LOGI(TAG, "Setting Wifi init config");
  CHECK(esp_wifi_init(&cfg), "Wifi init config");

  // Register event handler
  esp_event_handler_instance_t instance_any_id;
  esp_event_handler_instance_t instance_got_ip;
  ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, &instance_any_id));
  ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, &instance_got_ip));

  wifi_config_t config = {
    .sta = {
      .ssid = "",
      .password = "",
      .threshold.authmode = WIFI_AUTH_WPA2_PSK,
    }
  };
  ESP_LOGI(TAG, "Setting wifi config");
  strcpy((char *) config.sta.ssid, ssid);
  strcpy((char *) config.sta.password, passwd);

  ESP_LOGI(TAG, "Wifi is in station mode");
  CHECK(esp_wifi_set_mode(WIFI_MODE_STA), "WIFI MODE");

  ESP_LOGI(TAG, "Connecting to SSID %s", ssid);
  CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &config), "WIFI Config");

  ESP_LOGI(TAG, "Wifi is configured");
  CHECK(esp_wifi_start(), "WIFI start");
  ESP_LOGI(TAG, "Wifi is started");
  ESP_LOGI(TAG, "Wifi is in station mode");
  EventBits_t bits = xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_BIT | WIFI_FAIL_BIT, pdFALSE, pdFALSE, portMAX_DELAY);

  ESP_LOGI(TAG, "Connected");
}

void wifi_init(char *ssid, char *passwd) {
  CHECK(nvs_flash_init(), "NVS FLASH");
  ESP_LOGI(TAG, "Stating Connect to WIFI");
  wifi_connect(ssid, passwd);
};