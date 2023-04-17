/*
* ProjectName: Final Project
* FileName: main.c
*	version: 1
*
* Created:
* Author: Mitch Hekstra
*
* Operations: This program will:
*		
*
* Hardware Connection:
*	Inputs:
*	Outputs:

TODO:
- debug adc to read 2 channels at once
- debug CCW stepper motion
- debug password stuff
*/

#include "main.h"

volatile uint8_t home_var; //latch variable for homing function

int main(void)
{
	//initDebug();
	init_io();
	adc_init();
	Init_UART();
	PWM_init();
	init_INT();
	sei();
	
	char storedPass[8] = {"winning"};
	char enteredPass[8];
	uint8_t pass = 0;
	
	/*while (!pass)
	{
		//receive usart value
		if (newdata)
		{
			if (rx_char != 0x0D)//check for carriage return
			{
				rx_buffer[i] = rx_char;
				i++;
				newdata = 0;
			}
			
			else
			{
				i = 0;
				while(rx_buffer[i])
				{
					enteredPass[i] = rx_buffer[i];
					i++;
				}
				i = 0;
				newdata = 0;
				
				//compare uart value to password
				uint8_t sum = 0;
				uint8_t cmpVal = 0;
				while (enteredPass[i])
				{
					cmpVal = (enteredPass[i] - storedPass[i]);
					
					sum = sum + cmpVal;
				}
				if (sum == 0)
				{
					pass = 1;
				}
				else
				{
					UART_out('F');
				}
			}
		}
	}*/
	////homing loop
	home_var = 0; 
	//move the stepper motor CCW until limit switch is hit.
	//while (home_var == 0)
	//{
		//for (uint8_t i = 0; i < 8; i++)
		//{
			//stepper_output = half[i];
			//_delay_ms(3);
		//}
	//}
	
	//after motor is calibrated, PBs can be used to move stepper
	while (1)
	{
		stepper_movement();
		//ADC_controlled_PWM_OCR3A();
		//ADC_controlled_PWM_OCR3B();

	}

}


ISR(INT1_vect)
{
	home_var = 1;
}

ISR(USART0_RX_vect) //Receiver interrupt
{
	rx_char = UDR0; //Defines rx_ char as UDRO
	newdata = 1;
}


void init_INT(void)
{
	EICRA = (1<<ISC11);
	EIMSK = (1<<INT1);
}

void init_io(void)
{
	DDRC = 0x00;				//PB input
	
	DDRF = ~((1<<PF0)|(1<<PF1));//potentiometer input
	
	DDRE = 0x18;				//Servo PWM output
	DDRE |= 0x02;				//port E1 for UART output
	PORTE = 0x00;
	
	DDRK = 0xFF;				//stepper output
	PORTK = 0x00;
		
	DDRD = ~(1<<INT0);			//set only portd0 to input.
}