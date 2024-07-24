#include "driver/gpio.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>

#define PUSH_BUTTON_WHITE 25
#define PUSH_BUTTON_BLUE 26
#define LED 15

#define DEBOUNCE_DELAY_MS 50

void init(char *app_name) {
  gpio_set_direction(PUSH_BUTTON_BLUE, GPIO_MODE_INPUT);
  gpio_set_direction(PUSH_BUTTON_WHITE, GPIO_MODE_INPUT);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);

  ESP_LOGI(app_name, ":: INIT DONE");
}

void app_main(void) {
  char *ourTaskName = "TWO BUTTONS APP";
  ESP_LOGI(ourTaskName, "Hello World");

  init(ourTaskName);

  bool lastWhitePressed = false;
  bool lastBluePressed = false;

  bool WHITE_PRESSED = false;
  bool BLUE_PRESSED = false;

  gpio_reset_pin(LED);
  gpio_set_level(LED, 0); // Turn LED OFF

  while (true) {
    bool currentWhitePressed = gpio_get_level(PUSH_BUTTON_WHITE) == 0;
    bool currentBluePressed = gpio_get_level(PUSH_BUTTON_BLUE) == 0;
    vTaskDelay(DEBOUNCE_DELAY_MS / portTICK_PERIOD_MS);
    if (gpio_get_level(PUSH_BUTTON_WHITE) == 0) {
      currentWhitePressed = true;
    } else {
      currentWhitePressed = false;
    }

    if (gpio_get_level(PUSH_BUTTON_BLUE) == 0) {
      currentBluePressed = true;
    } else {
      currentBluePressed = false;
    }

    if (currentWhitePressed != lastWhitePressed) {
      WHITE_PRESSED = currentWhitePressed;
      BLUE_PRESSED = !currentWhitePressed;
    }

    if (currentBluePressed != lastBluePressed) {
      BLUE_PRESSED = currentBluePressed;
      WHITE_PRESSED = !currentBluePressed;
    }

    // Update LED state based on button press
    if (BLUE_PRESSED) {
      gpio_set_level(LED, 1); // Turn LED ON
    } else if (WHITE_PRESSED) {
      gpio_set_level(LED, 0); // Turn LED OFF
    }

    // Update last button states for next iteration
    lastWhitePressed = currentWhitePressed;
    lastBluePressed = currentBluePressed;

    vTaskDelay(100 / portTICK_PERIOD_MS); // Short delay to reduce CPU usage
  }
}
