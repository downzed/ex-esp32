#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "font8x8_basic.h"
#include "ssd1306.h"

#define tag "SSD1306"

#define PUSH_BUTTON 23
#define LED 5

void app_main(void) {
  SSD1306_t dev;
  int top;
  /*int center, top, bottom;*/
  /*char lineChar[20];*/

  gpio_set_direction(PUSH_BUTTON, GPIO_MODE_INPUT);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  ESP_LOGI(tag, "INTERFACE is i2c");
  ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d", CONFIG_SDA_GPIO);
  ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d", CONFIG_SCL_GPIO);
  ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d", CONFIG_RESET_GPIO);
  i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);

  ESP_LOGI(tag, "Panel is 128x64");
  ssd1306_init(&dev, 128, 64);

  gpio_set_level(LED, 0);
  ssd1306_clear_screen(&dev, false);
  ssd1306_contrast(&dev, 0xff);
  ssd1306_display_text_x3(&dev, 0, "Hello", 5, false);
  vTaskDelay(3000 / portTICK_PERIOD_MS);

  while (1) {
    gpio_set_level(LED, 0);

    if (gpio_get_level(PUSH_BUTTON) == 1) {
      ESP_LOGI(tag, "Button pressed");
      ssd1306_clear_screen(&dev, false);
      gpio_set_level(LED, 1);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      ssd1306_contrast(&dev, 0xff);
      ssd1306_display_text_x3(&dev, 0, "Marcus!", 7, false);
      vTaskDelay(5000 / portTICK_PERIOD_MS);
      esp_restart();
    } else {
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      gpio_set_level(LED, 0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      /*esp_restart();*/
    }
  }
}
