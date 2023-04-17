/*
 * my_delays.h
 *
 * Created: 2/22/2023 2:31:52 PM
 *  Author: mitch
 *
 */ 


#ifndef MY_DELAYS_H_
#define MY_DELAYS_H_

void init_PWM(void);
void init_timer(void);
void delay_1ms(uint16_t);
void myPWM(uint16_t duty_cycle);
void ramp_up_delay_n_steps (uint8_t start, uint8_t end, uint16_t ms_time, uint8_t num_steps);


#endif /* MY_DELAYS_H_ */