#include <reg51.h>
#include <uart.h>
#include <pwm.h>

float pwm_freq,duty_ratio;
extern unsigned char buffer;
extern unsigned int num;

void UART_Init(unsigned long baudrate)
{	TMOD=0x20; // 8bit auto reload timer1
	SCON=0x50; // Serial mode 1, 8 bit data, 1 stop bit, 1 start bit and Enable Receiving
	TH1= 256 - f_osc / (unsigned long)(6*32*baudrate); 
	TR1=1;
	EA=1;
	ES=1;
}

void UART_Receive(void) interrupt 4
{
	/*if(RI==1)
	{ RI=0;
		buffer = SBUF;
		if(buffer == 'f')
		{	pwm_freq=((float)(num)/10.0);
			num=0;
		}
		else if(buffer == 'd')
		{	duty_ratio=((float)(num)/100.0);
			num=0;
			pwm(pwm_freq,duty_ratio);
		}
		else
		{num =  num*10 + (buffer-'0');
		}
	}*/
}

void UART_Transmitchar(unsigned char x)
{	
	SBUF=x;
	while(TI==0);
	TI=0;
	
}
/*
void UART_Transmitnumber(int num)
{	unsigned char num0,num1,num2,num3;
	if(num<0)
	{	UART_Transmitchar('-');
		num*=(-1);
	}
		num0=num/1000;
        num1=(num%1000)/100;
		num2=(num%100)/10;
		num3=(num%10);
	
    if(num>9999)
    {   UART_Transmitstring("Number is too large");
        UART_Transmitchar(0x0D);
    }
	else if(num>999)
	{	
		UART_Transmitchar(num0+'0');
		UART_Transmitchar(num1+'0');
		UART_Transmitchar(num2+'0');
		UART_Transmitchar(num3+'0');
	}
	else if(num>99)
	{	UART_Transmitchar(num1+'0');
		UART_Transmitchar(num2+'0');
		UART_Transmitchar(num3+'0');
	}
	else if(num>9)
	{
		UART_Transmitchar(num2+'0');
		UART_Transmitchar(num3+'0');
	}
	else if(num>=0)
	{
	UART_Transmitchar(num+'0');
	}
	
}*/

void UART_Transmitstring(char* str)
{	while(*str !=0)
	{UART_Transmitchar(*str);
	 str++;
	}
}