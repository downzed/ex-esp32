#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define BLINK_LED 5
#define BLINK_LED_BUILTIN 2
#define PUSH_BUTTON 23

void app_main(void) {

  char *ourTaskName = pcTaskGetName(NULL);
  ESP_LOGI(ourTaskName, "Hello, World!");

  gpio_set_direction(PUSH_BUTTON, GPIO_MODE_INPUT);

  gpio_reset_pin(BLINK_LED);
  gpio_set_direction(BLINK_LED, GPIO_MODE_OUTPUT);
  /*gpio_set_direction(BLINK_LED_BUILTIN, GPIO_MODE_OUTPUT);*/

  gpio_set_level(BLINK_LED, 0);
  /*gpio_set_level(BLINK_LED_BUILTIN, 0);*/
  while (1) {
    if (gpio_get_level(PUSH_BUTTON) == 1) {
      ESP_LOGI(ourTaskName, "Pressed!");
      gpio_set_level(BLINK_LED, 1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      /*gpio_set_level(BLINK_LED_BUILTIN, 0);*/
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    } else {
      gpio_set_level(BLINK_LED, 0);
      /*gpio_set_level(BLINK_LED_BUILTIN, 1);*/
    }
    vTaskDelay(1);

    /*gpio_set_level(BLINK_LED, 1);*/
    /*vTaskDelay(1000 / portTICK_PERIOD_MS);*/
    /*gpio_set_level(BLINK_LED, 0);*/
    /*vTaskDelay(1000 / portTICK_PERIOD_MS);*/
  }
}
