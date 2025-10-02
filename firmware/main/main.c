/*
 * main.c - Entry point for fenstersensor firmware
 *
 * AI-generated scaffold. Review logic and security before production use.
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

void app_main(void)
{
    printf("Fenstersensor firmware started.\n");
    // TODO: Implement sensor logic
    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
