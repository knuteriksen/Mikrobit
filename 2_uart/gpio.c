#include "gpio.h"
#include <stdint.h>

void gpio_init() {
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
}
