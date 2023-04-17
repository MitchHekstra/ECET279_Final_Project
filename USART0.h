/*
 * USART0.h
 *
 * Created: 3/22/2023 2:29:22 PM
 *  Author: mitch
 */ 


#ifndef USART0_H_
#define USART0_H_

#define SETUP 0b0

volatile uint8_t rx_char;
volatile char rx_buffer[25];

void Init_UART(void);
void UART_out(uint8_t);


#endif /* USART0_H_ */