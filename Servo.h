

#ifndef SERVO_H_
#define SERVO_H_


#include <avr/io.h>


void PWM_init(void);
void adc_init(void);
uint16_t ADC_10bit(uint8_t channel);
void ADC_controlled_PWM_OCR3A(void);
void ADC_controlled_PWM_OCR3B(void);


#endif /* SERVO_H_ */