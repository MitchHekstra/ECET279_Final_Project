/*
 * USART0.c
 *
 * Created: 3/22/2023 2:29:09 PM
 *  Author: mitch
 */ 

#include <avr/io.h>
#include "USART0.h"
#include <util/delay.h>

void Init_UART(void)
{
	UBRR0L = 103; //data-sheet-recommended UBRR value for 9600 baud
	UBRR0H = 0x00;
	UCSR0A = 0x00;
	//Rx Int Enable; Rx Enable; Tx Enable
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	//8 data bits;
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void UART_out(uint8_t ch)
{
	while ((UCSR0A & (1<<UDRE0)) == 0)
	{//Wait for UART to be able to accept new data
	}
	
	UDR0 = ch; //load character to be transmitted
}

