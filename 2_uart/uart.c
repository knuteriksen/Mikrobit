#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REG*)0x40002000)


typedef struct {
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RESERVED0[3];
	volatile uint32_t SUSPEND;
	volatile uint32_t RESERVED1[56];

	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RESERVEDa[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RESERVED2[1];
	volatile uint32_t ERROR;
	volatile uint32_t RESERVED3[7];
	volatile uint32_t RXTO;
	volatile uint32_t RESERVED4[110];

	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED5[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RESERVED6[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RESERVED7[1];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RESERVED8[1];
	volatile uint32_t BAUDRATE;		//skal være 9600
	volatile uint32_t RESERVED9[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;


void uart_init() {
	
	GPIO->PIN_CNF[25] = 0; // set pin #25 as input
	GPIO->PIN_CNF[24] = 1; // set pin #24 as output

	UART->PSELRXD = 25;
	UART->PSELTXD = 24;
	UART->PSELCTS = 0xFFFFFFFF; //har ikke flytkontroll så disse blir disabled
	UART->PSELRTS = 0xFFFFFFFF;

	UART->BAUDRATE = 0x00275000; //Set baudrate to 9600

	UART->ENABLE = 4;  // Turn on UART (verdi kommer fra datablad)

	UART->STARTRX = 1; // Start recieve

}

void uart_send(char letter) {

	UART->STARTTX = 1;  //start transmitting
	UART->TXDRDY = 0; 
	UART->TXD = letter; //write letter to TXD
	while (!UART-> TXDRDY);
	UART->STOPTX = 1; 
}

char uart_read() {
	char letter = '\0';
	if(UART->RXDRDY){ //vent til rxdrdy er klar
		letter = UART->RXD;
		UART->RXDRDY = 0;
	}
	return letter;
}


void micro_send() {
	if (!(GPIO->IN &(1 << 26))) { //sjekk om B er trykket inn
			uart_send('B');
	}

	if (!(GPIO->IN &(1 << 17))) { //sjekk om A knapp
			uart_send('A');
	}

}







