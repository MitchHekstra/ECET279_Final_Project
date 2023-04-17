/*
 * stepper_motor.c
 *
 * Created: 2/1/2023 2:16:49 PM
 *  Author: Mitch Hekstra
 */ 

#include "stepper_motor.h"

//stepper motor mode arrays
uint8_t wave[4] = {0x01, 0x02, 0x04, 0x08};
uint8_t full[4] = {0x03, 0x06, 0x0C, 0x09};
uint8_t half[8] = {0x09, 0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08};


//function definitions
void stepper_init(void)
{
	//NOT USED
}

void stepper_drive(char mode, uint8_t revolutions)
{
	//this guides what mode the stepper motor uses and how much to turn
	uint16_t steps = 0;
	
	switch (mode)
	{
		case 'W': //wave mode
		{
			steps = revolutions*2048/4; //512 steps/rev
			for (uint16_t i = 0; i < steps; i++)
			{
				for (uint16_t j = 0; j < 4; j++)
				{
					stepper_output = wave[j];
					_delay_ms(3); //at 3ms, 6.144s/rev or 9.765625rpm
				}
			}
			break;
		}
		case 'F': //full mode
		{
			steps = revolutions*2048/4;
			for (uint16_t i = 0; i < steps; i++)
			{
				for (uint16_t j = 0; j < 4; j++)
				{
					stepper_output = full[j];
					_delay_ms(3);
				}
			}
			break;
		}
		case 'H': ///half mode
		{
			steps = revolutions*2048/8; //twice as many steps/rev
			for (uint16_t i = 0; i < steps; i++)
			{
				for (uint16_t j = 0; j < 8; j++)
				{
					stepper_output = half[j];
					_delay_ms(3);//at 3ms, 12.288/rev or 4.8828125rpm
				}
			}
			break;
		}
	}
}

void stepper_position(uint16_t angle)
{
	//function for custom angle of rotation. always in half mode
	uint8_t steps = (angle / 0.703125); // 0.703125 deg/step
	for (uint16_t i = 0; i < steps; i++)
	{
		for (uint16_t j = 0; j < 8; j++)
		{
			stepper_output = half[j];
			_delay_ms(3);
		}
	}
}

void stepper_movement(void)
{
	//function for on-demand rotation in CW or CCW direction, always in half mode
	while (PINC == 0)
	{ //wait for pb to be pressed
		
		ADC_controlled_PWM_OCR3A();
		ADC_controlled_PWM_OCR3A();
	}
	while (PINC != 0)
	{ //once pb is pressed...
		if (PINC == 0x01) //CW motion
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				stepper_output = half[i];
				_delay_ms(5);
			}
		}
		
		if (PINC == 0x02) //CCW motion
		{
			for (uint8_t i = 8; i > 0; i--)
			{
				stepper_output = half[i];
				_delay_ms(5);
			}
		}
	}
}
