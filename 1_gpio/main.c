#include <stdint.h>



#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons as input
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	int sleep = 0;
	while(1){

		if (!(GPIO->IN &(1 << 26))){  //Check if button B is pressed//
			GPIO->OUTSET = (1 << 13 | 1 << 14 | 1 << 15);//turn on LED matrix if it is. //
		}  

		 if (!(GPIO->IN &(1 << 17))){ //Check if button A is pressed; //
		 GPIO->OUTCLR = (1 << 13 | 1 << 14 | 1 << 15);//turn off LED matrix if it is. //
		 }
		sleep = 10000;
		while(--sleep);
	}

	return 0;
}
