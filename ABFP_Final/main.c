#include <reg51.h>
#include <pwm.h>
#include <uart.h>

sbit pump = P1^2;
sbit ir = P3^2;
unsigned char buffer;
bit action_flag=0,savepin,check_flag=1;
unsigned long count[2];
unsigned int ovf_cnt,ovf_count[2],temp[2],num;
void delay(unsigned int);

int main(void)
{
	UART_Init(9600);
	UART_Transmitstring("UART is :P :Q :D ");
	
	init_timer0();              //initialize timer 0
	EA=1;
  pump=0;
	pwm(25,0.20);
	
	while(1)
	{	if(ir==1)
		{
			pwm_pin=0;
			TR0=0;
			UART_Transmitstring("pump is on ");
			UART_Transmitchar(0x0D);
			pump = 1;
			delay(1000);
			pump = 0;
			UART_Transmitstring("pump is off ");
			UART_Transmitchar(0x0D);
			delay(100);
			TR0=1;
			while(ir);
		}
	}
	
}

void delay(unsigned int x)
{
	unsigned int i,j;
	
	for(i=0;i<x;i++)
	for(j=0;j<500;j++);
}
