/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */
#include <stdint.h>
#include <stdbool.h>
#include "ulp_lp_core.h"
#include "ulp_lp_core_utils.h"
#include "ulp_lp_core_gpio.h"

#define BLINK_PIN LP_IO_NUM_2 // Define the GPIO pin connected to the LED
#define BLINK_DELAY_MS 500    // Define the delay in milliseconds between toggles

static bool led_state = false;

int main(void)
{
    // Initialize the GPIO pin as output
    ulp_lp_core_gpio_output_enable(BLINK_PIN);

    // Toggle the LED state
    led_state = !led_state;
    ulp_lp_core_gpio_set_level(BLINK_PIN, (int)led_state);

    // Delay for BLINK_DELAY_MS
    ulp_lp_core_delay_us(BLINK_DELAY_MS * 1000);

    /* ulp_lp_core_halt() is called automatically when main exits */
    return 0;
}