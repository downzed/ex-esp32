#include "esp_log.h"
#include <dht.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>

#include "ssd1306.h"

#define tag "SSD1306"

#define SENSOR_TYPE DHT_TYPE_DHT11
#define DHT_GPIO_PIN 5

#define OLED_RESET_GPIO -1
#define OLED_SCL_GPIO 21
#define OLED_SDA_GPIO 22

static const char *TAG = "LCD-DHT11 Test";
SSD1306_t dev;

void dht_test(void *pvParameters) {
  float temperature, humidity;

  while (1) {
    if (dht_read_float_data(SENSOR_TYPE, DHT_GPIO_PIN, &humidity,
                            &temperature) == ESP_OK) {
      ESP_LOGI(TAG, "Humidity: %.1f%% Temp: %.1fC\n", humidity, temperature);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      char temp[50]; // Buffer to hold the resulting string
      char hum[50];  // Buffer to hold the resulting string

      // Format the string with temperature value
      sprintf(temp, "Temp: %.1fC", temperature);
      sprintf(hum, "humidity: %.1f%%", humidity);

      ssd1306_display_text(&dev, 3, temp, 11, true);
      ssd1306_display_text(&dev, 5, hum, 15, true);
    }

    else {
      ESP_LOGE(TAG, "Could not read data from sensor\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      ssd1306_clear_screen(&dev, false);
      ssd1306_contrast(&dev, 0xff);
    }

    // If you read the sensor data too often, it will heat up
    // http://www.kandrsmith.org/RJS/Misc/Hygrometers/dht_sht_how_fast.html
    vTaskDelay(pdMS_TO_TICKS(4000));
  }
}

void init_oled(SSD1306_t *dev) {
  ESP_LOGI(tag, "OLED_SCL_GPIO=%d", OLED_SCL_GPIO);
  ESP_LOGI(tag, "OLED_SDA_GPIO=%d", OLED_SDA_GPIO);
  ESP_LOGI(tag, "OLED_RESET=%d", OLED_RESET_GPIO);
  i2c_master_init(dev, OLED_SDA_GPIO, OLED_SCL_GPIO, OLED_RESET_GPIO);

  ESP_LOGI(tag, "Panel is 128x64");

  ssd1306_init(dev, 128, 64);
  ssd1306_clear_screen(dev, false);
  ssd1306_display_text(dev, 0, "Welcome!", 8, false);
}

void app_main() {
  ESP_LOGI(TAG, "Initializing...");
  init_oled(&dev);
  xTaskCreate(dht_test, "dht_test", configMINIMAL_STACK_SIZE * 3, NULL, 5,
              NULL);
}
