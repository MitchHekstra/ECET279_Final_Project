/*
 * my_delays.c
 *
 * Created: 2/22/2023 2:31:24 PM
 *  Author: mitch
 *
 */ 

#include <avr/io.h>
#include "my_delays.h"

void init_PWM(void)
{
	TCCR3A = 0x02;     // set for PWM, mode 14
	TCCR3B = 0x18;     // set for PWM, mode 14
	TCCR3A = TCCR3A | 0x80; // set compare output mode to clear on match
	TCCR3B = TCCR3B | 0x02; // select clock prescale
	ICR3 = 40000;      // set the counter max value
	OCR3A = 3000;
	
	TCCR4A = 0x02;     // set for PWM, mode 14
	TCCR4B = 0x18;     // set for PWM, mode 14
	TCCR4A = TCCR4A | 0x80; // set compare output mode to clear on match
	TCCR4B = TCCR4B | 0x02; // select clock prescale
	ICR4 = 40000;      // set the counter max value
	OCR4A = 3000;
}

void init_timer(void)
{
	TCCR0A = 0;
	TCCR0B = 0;
}

void delay_1ms(uint16_t delay)
{
	for (uint16_t i = 0; i < delay; i++)
	{
		TCNT0 = 6;
		TCCR0B = (1<<CS01)|(1<<CS00); //start timer and 1024 prescale
		while ((TIFR0 & (1<<TOV0)) == 0)
		{ //WAITING UNTIL OVERFLOW FLAG SETS
		}
		TCCR0B = 0; //stop timer
		TIFR0 |= (1<<TOV0); //reset timer flag
	}
}

void myPWM(uint16_t duty_cycle)
{
	TCNT1 = 0;
	//Set output to value for duty cycle
	
	//9-bit PWM (mode 6); Set on compare match
	TCCR1A = (1<<WGM11) | (1<<COM1A1);
	//9-bit PWM (mode 6);
	TCCR1B = (1<<WGM12);
	//Start timer with 1 prescaler
	TCCR1B |= (1<<CS11);
	
	OCR1A = (duty_cycle/2);
	//OCR1A = duty_cycle/2;
}

void ramp_up_delay_n_steps(uint8_t start, uint8_t end, uint16_t ms_time, uint8_t num_steps)
{
	// a. calculate change in duty cycle / step = duty_cycle_change
	float duty_cycle_change = (end-start)/num_steps;
	 
	// c. calculate time for each step = step_time
	float step_time = ms_time/num_steps;
	 
	// d. Loop for number of steps
	for (uint8_t i = start; i < end+duty_cycle_change; i+=duty_cycle_change)
	{
 		myPWM(i); // f. Change OCR1A
 		delay_1ms(step_time); // g. Delay step_time
	}
}




