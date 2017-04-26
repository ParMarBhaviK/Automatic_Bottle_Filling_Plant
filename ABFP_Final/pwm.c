#include <reg51.h>
#include <pwm.h>

extern unsigned long count[2];
extern unsigned int ovf_cnt,ovf_count[2],temp[2];

//timer inialization

void init_timer0(void)	
{
	TMOD &= 0xF0;
	TMOD |= 0X01;
	
	ET0=1;
	EA=1;
	
}

void pwm(float pwm_freq,float duty_ratio)
{ 
	count[1] = (unsigned long)((f_timer*duty_ratio)/pwm_freq);
	count[0] = (unsigned long)((f_timer*(1.0f-duty_ratio))/pwm_freq);
	
	ovf_count[1] = count[1]/65536;
	ovf_count[0] = count[0]/65536;
	temp[1] = 65536-(count[1]%65536UL); 
	temp[0] = 65536-(count[0]%65536UL);
	

	pwm_pin=0;
	ovf_cnt=ovf_count[pwm_pin];
	
	TH0=(temp[pwm_pin]>>8)&0xff;
	TL0=temp[pwm_pin]&0xff;

	TR0	=1;
}

//timer ISR

void timer0_isr(void) interrupt 1
{
	TR0=0;

		if(ovf_cnt>0)
		{ovf_cnt--;
		}
		else
		{	pwm_pin =~ pwm_pin;
			TH0=(temp[pwm_pin]>>8)&0xff;
			TL0=temp[pwm_pin]&0xff;
			ovf_cnt=ovf_count[pwm_pin];
		}

	TF0=0;                  //clear the timer overflow flag
	TR0=1;                  //start timer 0
}
