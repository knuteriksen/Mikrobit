#include "twi.h"
#include "gpio.h"
void twi_init () {

	GPIO->PIN_CNF[0] = 0;
	GPIO->PIN_CNF[30] = 0;
	
	TWI0->PSELSCL = 0;
	TWI0->PSELSDA = 30;
	TWI0->FREQUENCY = 0x01980000;  // set speed to 100 kbps
	TWI0->ENBALE = 5; //enbale twi0
}



void twi_multi_read(uint8_t slave_address, uint8_t start_register, int registers_to_read,
	uint8_t * data_buffer) {

	TWI0->ADDRESS = slave_address;


}