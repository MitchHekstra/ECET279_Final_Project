/*
 * main.h
 *
 * Created: 4/5/2023 5:32:55 PM
 *  Author: mitch
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include "my_delays.h"
#include "Servo.h"
#include "USART0.h"
//#include "EEPROM.h"
#include "Debugger.h"
#include "stepper_motor.h"
#include <avr/interrupt.h>


volatile uint8_t array_index;
volatile uint8_t newdata = 0;
volatile uint8_t i = 0;

void init_INT(void);
void init_io(void);

#endif /* MAIN_H_ */