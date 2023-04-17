/*
 * stepper_motor.h
 *
 * Created: 2/1/2023 2:17:18 PM
 *  Author: mitch
 */ 


#ifndef STEPPER_MOTOR_H_
#define STEPPER_MOTOR_H_

//set clk speed for delay library
#define F_CPU 16000000UL

//include files
#include <avr/io.h>
#include <util/delay.h>

//prototypes
void stepper_drive(char, uint8_t);
void stepper_init(void);
void stepper_position(uint16_t);
void stepper_movement(void);

//Pushbutton mode definition - PINC
#define wave_step 0x01
#define full_step 0x02
#define half_step 0x04
#define pos		  0x08

#define stepper_output PORTK

//global variables
extern uint8_t wave[4];
extern uint8_t full[4];
extern uint8_t half[8];

#endif /* STEPPER_MOTOR_H_ */