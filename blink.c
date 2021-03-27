/* Program to demonstrate impact of XIP cache on program performance 
 * of raspberry pi pico. 
 * Author : sreekesh.star@gmail.com 
 **/

#include "pico/stdlib.h"
#include <stdint.h>

/* Base address for XIP access, cacheable, allocating - Normal cache operation */
#define XIP_CACHE_ADDR_BASE (0x10000000)

/* Base address for XIP access, non-cacheable, non-allocating - Bypass cache completely */
#define XIP_BYPASS_CACHE_ADDR_BASE (0x13000000)

const uint LED_PIN = 18;

typedef void (*func_ptr_t)(void);

void toggle_led(void);
void my_delay(void);

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    func_ptr_t toggle_led_func = &toggle_led;
    func_ptr_t toggle_led_from_flash = (func_ptr_t) ( ( (uint32_t)toggle_led - XIP_CACHE_ADDR_BASE ) + XIP_BYPASS_CACHE_ADDR_BASE );

//    toggle_led_from_flash();	// execute function bypassing XIP cache

    toggle_led();	// execute function using XIP cache
}


void toggle_led(void)
{
    while (true) {
        gpio_put(LED_PIN, 1);
	my_delay();
        gpio_put(LED_PIN, 0);
	my_delay();
    }
}

void my_delay(void)
{
    uint32_t i;
    volatile uint32_t a;
    for(i=0; i<10000000U; i++)
    {
	    a=i;
    }
}
