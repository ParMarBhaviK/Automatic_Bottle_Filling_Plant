#ifndef _PWM_H
#define _PWM_H

#define f_osc 18432000.0f // in Hz
#define clock_mode 6.0f
#define f_timer f_osc/clock_mode

sbit pwm_pin= P1^0;

void init_timer0(void);
void pwm(float,float);

#endif