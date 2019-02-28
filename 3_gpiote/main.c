#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main() {
	
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}


	GPIOTE->CONFIG[0] = ((1 << 0) | (17 << 8) | (2 << 16));
	for (int i = 1; i<4 ; i++) {
		GPIOTE->CONFIG[i] = ((3 << 0) | ((12+i) << 8) | (3 << 16) | (1 << 20));
	}

	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);   //config chan 0
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);  // config chan 1
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

	PPI->CHENSET = (1 | 1 << 1 | 1 << 2);

	while(1);

	return 0;

}