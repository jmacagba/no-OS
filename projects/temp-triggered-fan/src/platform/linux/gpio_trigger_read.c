#include <linux/gpio.h>
#include "no_os_gpio.h"
#include "parameters.h"
#include "no_os_delay.h"
#include "no_os_print_log.h"
#include <stdio.h>
int main() {
    int pin = 2;
    uint8_t gpio_state = 0;
    
    // Acquire file descriptior for pin 
    struct no_os_gpio_desc *descriptor;
    struct no_os_gpio_init_param param = {
        .port = 0,
        .number = pin,
        .pull = NO_OS_PULL_NONE,
        .platform_ops = GPIO_OPS,
        .extra = NULL 
        };
    
    no_os_gpio_get(&descriptor, &param); 
    
    // Set GPIO output to HIGH
    no_os_gpio_direction_output(descriptor, NO_OS_GPIO_HIGH);
    no_os_gpio_get_value(descriptor, & gpio_state);
    pr_info("This is GPIO %d current state: %u\n", pin, gpio_state);
    no_os_mdelay(1000);
    
    // Set GPIO output to LOW
    no_os_gpio_direction_output(descriptor, NO_OS_GPIO_LOW);
    no_os_gpio_get_value(descriptor, & gpio_state);
    pr_info("This is GPIO %d current state: %u\n", pin, gpio_state);
    no_os_mdelay(1000);
    
    
    //Close descriptor
    no_os_gpio_remove(descriptor);
    
    return 0;
}
