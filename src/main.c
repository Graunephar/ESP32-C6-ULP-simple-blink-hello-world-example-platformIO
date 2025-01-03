
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"
#include "ulp_lp_core.h"
#include "esp_err.h"

static const char *TAG = "example";

/* Use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO 8
#define BLINK_PERIOD 5000

static uint8_t s_led_state = 0;

static led_strip_handle_t led_strip;

extern const uint8_t bin_start[] asm("_binary_ulp_main_bin_start"); //refering to app name ulp_main defined in CMakelists.txt
extern const uint8_t bin_end[]   asm("_binary_ulp_main_bin_end"); //refering to app name ulp_main defined in CMakelists.txt

void start_ulp_program() {
    // Change: Load the ULP binary into RTC memory
    ESP_ERROR_CHECK(ulp_lp_core_load_binary(bin_start, (bin_end - bin_start)));

    // Change: Configure the ULP LP core wake-up source and timer
    ulp_lp_core_cfg_t cfg = {
        .wakeup_source = ULP_LP_CORE_WAKEUP_SOURCE_LP_TIMER, // Wake up using LP timer
        .lp_timer_sleep_duration_us = 1000000,              // 1-second sleep duration
    };

    // Change: Start the ULP LP core program
    ESP_ERROR_CHECK(ulp_lp_core_run(&cfg));
}

static void configure_led(void) {

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
    start_ulp_program();

    //this is by design a very simple main loop to keep the ULP busy but also give it time to sleep. 
    //Kept simple because this loop is not the point of this example
    while (1) {

        ESP_LOGI(TAG, "Turning the LED RED");
        led_strip_set_pixel(led_strip, 0, 16, 0, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Turning the GREEN RED");
        led_strip_set_pixel(led_strip, 0, 0, 16, 0);
        led_strip_refresh(led_strip);
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);

        ESP_LOGI(TAG, "Turning the LED BLUE");
        led_strip_set_pixel(led_strip, 0, 0, 0, 16);
        led_strip_refresh(led_strip);
        vTaskDelay(BLINK_PERIOD / portTICK_PERIOD_MS);



    }
}