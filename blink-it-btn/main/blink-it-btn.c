#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "esp_log.h"

#define BLINK_LED 5
#define PUSH_BUTTON 23

void init_components() {
  gpio_set_direction(PUSH_BUTTON, GPIO_MODE_INPUT);

  gpio_reset_pin(BLINK_LED);
  gpio_set_direction(BLINK_LED, GPIO_MODE_OUTPUT);

  gpio_set_level(BLINK_LED, 0);
}

void app_main(void) {

  char *ourTaskName = pcTaskGetName(NULL);
  ESP_LOGI(ourTaskName, "Hello, World!");

  init_components();

  bool ledState = false;
  bool buttonState = false;
  bool lastButtonState = false;

  while (1) {
    buttonState = gpio_get_level(PUSH_BUTTON);

    // Check if the button state has changed
    if (buttonState != lastButtonState) {
      // Debounce delay
      vTaskDelay(50 / portTICK_PERIOD_MS);

      // Check the button state again after the delay
      if (buttonState == gpio_get_level(PUSH_BUTTON) && buttonState == 1) {
        ledState = !ledState;
        gpio_set_level(BLINK_LED, ledState);
        ESP_LOGI(ourTaskName, "Button Pressed! LED state: %d", ledState);
      }

      // Update the last button state
      lastButtonState = buttonState;
    }

    // Yield to other tasks
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
