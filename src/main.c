/* Blink Example from https://github.com/espressif/esp-idf/blob/master/examples/get-started/blink/main/blink_example_main.c

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 8
#define BLINK_PERIOD 5000

static uint8_t s_led_state = 0;

static led_strip_handle_t led_strip;


static void configure_led(void)
{
    ESP_LOGI(TAG, "Example configured to blink addressable LED!");
    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,
        .max_leds = 1, // at least one LED on board
    };

    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = false,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

    /* Set all LED off to clear all pixels */
    led_strip_clear(led_strip);
}


void app_main(void)
{

    /* Configure the peripheral according to the LED type */
    configure_led();


    //this is by design a very simple main loop to keep the ULP busy but also give it time to sleep. 
    //Kept simple because this loop is not the point of this example
    while (1) {

        ESP_LOGI(TAG, "Turning the LED RED");
        led_strip_set_pixel(led_strip, 0, 255, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Turning the GREEN RED");
        led_strip_set_pixel(led_strip, 0, 0, 255, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Turning the LED BLUE");
        led_strip_set_pixel(led_strip, 0, 0, 0, 255);
        led_strip_refresh(led_strip);
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);



    }
}