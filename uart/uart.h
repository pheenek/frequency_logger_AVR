
#ifndef UART_H
#define UART_H

#include "../global_defs.h"

// define some macros
#define BAUDRATE    57600                               // define baudrate
#define MYUBRR  ((F_CPU/16/BAUDRATE)-1)                  // set baudrate rate value for UBRR
// #define MYUBRR  51

// function to initialize UART
void USART_Init();

void USART_Transmit(unsigned char data);

unsigned char USART_Receive(void);

void sendString(char *data);

#endif
