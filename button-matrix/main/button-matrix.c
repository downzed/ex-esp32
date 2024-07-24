#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#define ROW0 GPIO_NUM_15
#define ROW1 GPIO_NUM_4
#define COL0 GPIO_NUM_25
#define COL1 GPIO_NUM_26

int rows[] = {4, 15};
int cols[] = {25, 26};

void app_main() {
  // Initialization code here
  printf("Hello, ESP32!\n");

  // Configure row pins as outputs and set them to HIGH
  for (int i = 0; i < 2; i++) {
    gpio_reset_pin(rows[i]);
    gpio_set_direction(rows[i], GPIO_MODE_INPUT);
    gpio_set_level(rows[i], 1);
  }

  // Configure column pins as inputs with pull-up resistors
  for (int i = 0; i < 2; i++) {
    gpio_reset_pin(cols[i]);
    gpio_set_direction(cols[i], GPIO_MODE_INPUT);
    /*gpio_set_pull_mode(cols[i], GPIO_PULLUP_ONLY);*/
  }

  // Main loop
  while (true) {
    for (int i = 0; i < 2; i++) {
      gpio_set_level(rows[i], 0);
      for (int j = 0; j < 2; j++) {
        if (gpio_get_level(cols[j]) == 0) {
          printf("Row %d Col %d PRESSED!\n", i, j);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
      }
      gpio_set_level(rows[i], 1);
    }
  }
}
