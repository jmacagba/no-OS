#include <linux/gpio.h>
#include "no_os_gpio.h"
#include "parameters.h"
#include <stdio.h>
int main() {
    int pin = 586; // Pin number is not straightforward 
    
    
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
    sleep(1);
    
    // Set GPIO output to LOW
    no_os_gpio_direction_output(descriptor, NO_OS_GPIO_LOW);
    sleep(1);
    
    //Close descriptor
    no_os_gpio_remove(descriptor);
    
    return 0;
}
