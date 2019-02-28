#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "gpio.h"



int main(){
	uart_init();
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	gpio_init();


	while (1) {
		micro_send();
	}
	
	return 0;
}