
#include "Servo.h"

void PWM_init(void)
{
	
	TCCR3A = 0x02;     // set for PWM, mode 14
	TCCR3B = 0x18;     // set for PWM, mode 14
	TCCR3A = TCCR3A | 0x80; // set compare output mode to clear on match
	TCCR3B = TCCR3B | 0x02; // select clock prescale
	ICR3 = 40000;      // set the counter max value 
	
	//TCCR4A = 0x02;     // set for PWM, mode 14
	//TCCR4B = 0x18;     // set for PWM, mode 14
	//TCCR4A = TCCR4A | 0x80; // set compare output mode to clear on match
	//TCCR4B = TCCR4B | 0x02; // select clock prescale
	//ICR4 = 40000;      // set the counter max value
}

void adc_init(void)
{
	ADCSRA |= (1<<ADEN) | (1<<ADPS0)|(1<<ADPS1) | (1<<ADATE); //enable ADC; Prescale of 64
	ADMUX |= (1<<REFS0); //| (1<<MUX0)|(1<<MUX1); //channel 1 & 2

}
 
uint16_t ADC_10bit(uint8_t channel)
{
	uint16_t result = 0;
	
	ADMUX &= 0xFC; //clear mux channel before setting new one
	ADMUX = ADMUX | channel;
	ADCSRA |= (1<<ADSC); //start conversion
	
	while ((ADCSRA & (1<<ADIF)) == 0)
	{ //wait for interrupt flag to set
	} //indicating conversion has finished
	
	result = ADCL; //freeze ADCH/ADCL and store ADCL
	result = result | (ADCH<<8); //add ADCH to the left side of ADCL
	ADCSRA |= (1<<ADIF);
	return result;
}

void ADC_controlled_PWM_OCR3A(void)
{
	uint16_t pulse_width = (ADC_10bit(1)*4) + 1000;          // read the ADC value at channel 1
	OCR3A = pulse_width;
}

void ADC_controlled_PWM_OCR3B(void)
{
	uint16_t pulse_width = (ADC_10bit(2)*4) + 1000;          // read the ADC value at channel 2
	OCR3B = pulse_width;
}


/*if ((PINC & 0x01) == 1)
		{
			OCR3A = pulse_width;
			pulse_width += 100;
			ms_Delay(500);
			if (pulse_width >= 2100)
			{
				while (pulse_width > 1000)
				{
					pulse_width -= 100;
					OCR3A = pulse_width;
					ms_Delay(500);
				}
				
			}
		} 
		else
		{
			pulse_width = read_10Bit_ADC_channel(0);          // read the ADC value at channel 0
			printf("pulse width is %u", pulse_width);
			OCR3A = pulse_width + 1000;
		}
*/		