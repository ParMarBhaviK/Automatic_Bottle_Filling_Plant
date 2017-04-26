#ifndef _uart_h	
#define _uart_h

// 0x0D for new line and 0x20 for space 

void UART_Init(unsigned long baudrate);
void UART_Receive(void);
void UART_Transmitchar(unsigned char x);
void UART_Transmitnumber(int num);
void UART_Transmitstring(char* str);

#endif

