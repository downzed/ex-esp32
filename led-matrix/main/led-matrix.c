#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define ROW1_GPIO 19
#define ROW2_GPIO 21
#define COL1_GPIO 22
#define COL2_GPIO 23

void init_leds() {
  gpio_set_direction(ROW1_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_direction(ROW2_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_direction(COL1_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_direction(COL2_GPIO, GPIO_MODE_OUTPUT);
}

void turn_on_led(int row, int col) {
  // Set the row pin to high and column pin to low
  gpio_set_level(row, 1);
  gpio_set_level(col, 0);
}

void turn_off_led(int row, int col) {
  // Set the row pin to low
  gpio_set_level(row, 0);
  gpio_set_level(col, 1);
}

void app_main(void) {
  // Initialize GPIO
  init_leds();
  while (1) {
    turn_on_led(ROW1_GPIO, COL1_GPIO);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    turn_off_led(ROW1_GPIO, COL1_GPIO);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
