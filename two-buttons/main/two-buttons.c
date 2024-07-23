#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>
#include <stdlib.h>

#define PUSH_BUTTON_WHITE 23
#define PUSH_BUTTON_BLUE 22
#define LED 19

void init(char *app_name) {
  gpio_set_direction(PUSH_BUTTON_BLUE, GPIO_MODE_INPUT);
  gpio_set_direction(PUSH_BUTTON_WHITE, GPIO_MODE_INPUT);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  ESP_LOGI(app_name, ":: INIT DONE");
}

void app_main(void) {
  char *ourTaskName = "TWO BUTTONS APP";
  /*pcTaskGetName(NULL);*/
  ESP_LOGI(ourTaskName, "Hello World");

  init(ourTaskName);

  bool WHITE_PRESSED = false;
  bool BLUE_PRESSED = false;

  while (true) {
    if (gpio_get_level(PUSH_BUTTON_BLUE) == 1) {
      WHITE_PRESSED = false;
      BLUE_PRESSED = true;
      vTaskDelay(500 / portTICK_PERIOD_MS);
      ESP_LOGI(ourTaskName, "BLUE PRESSED");
    }
    if (gpio_get_level(PUSH_BUTTON_WHITE) == 1) {
      BLUE_PRESSED = false;
      WHITE_PRESSED = true;
      vTaskDelay(500 / portTICK_PERIOD_MS);
      ESP_LOGI(ourTaskName, "WHITE PRESSED");
    }

    if (BLUE_PRESSED) {
      gpio_set_level(LED, 1);
    }

    if (WHITE_PRESSED) {
      gpio_set_level(LED, 0);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
