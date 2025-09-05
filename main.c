#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_OUT_W1TS_REG  0x60004008
#define GPIO_OUT_W1TC_REG  0x6000400C
#define GPIO_ENABLE_REG    0x60004020

#define GPIO5             5
#define DELAY_TIME_MS     500

void app_main(void)
{
    volatile uint32_t* gpio_out_w1ts_reg = (volatile uint32_t*) GPIO_OUT_W1TS_REG;
    volatile uint32_t* gpio_out_w1tc_reg = (volatile uint32_t*) GPIO_OUT_W1TC_REG;
    volatile uint32_t* gpio_enable_reg   = (volatile uint32_t*) GPIO_ENABLE_REG;

    // Enable GPIO5 as output (preserves other pins by |= instead of =)
    *gpio_enable_reg |= (1 << GPIO5);

    while(1) {
        // Set GPIO5 HIGH
        *gpio_out_w1ts_reg = (1 << GPIO5);
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));

        // Set GPIO5 LOW
        *gpio_out_w1tc_reg = (1 << GPIO5);
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    }
}
