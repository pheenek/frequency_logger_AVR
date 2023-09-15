/**
 * @file 		uart.h 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This file contains some basic functions to set up, send
 *              and received data over UART0 on the ATMega328P microcontroller
 * 
 * @version 	0.1 
 * 
 * @date 		2023-09-15
 * 
 * ***************************************************************************
 * @copyright Copyright (c) 2023, Stephen Kairu
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the “Software”), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 * OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * ***************************************************************************
 * 
 */
#ifndef UART_H
#define UART_H

#include "../global_defs.h"

// define some macros
#define BAUDRATE    57600                               // define baudrate
#define MYUBRR  ((F_CPU/16/BAUDRATE)-1)                  // set baudrate rate value for UBRR
// #define MYUBRR  51

/**
 * @brief	 Function to initialize UART with BAUDRATE value
 * 
 * @param none
 * @return none 
 */
void USART_Init(void);

/**
 * @brief	 Function to transmit a single 8-bit value over UART
 * 
 * @param data -> Character to be transmitted
 * @return none
 */
void USART_Transmit(unsigned char data);

/**
 * @brief	 Function to receive a single 8-bit value over UART
 * 
 * @param none
 * @return unsigned char -> character received
 */
unsigned char USART_Receive(void);

/**
 * @brief	 Function to send a string of characters over UART
 *          The string is terminated with \r\n
 * 
 * @param data -> pointer to character-string
 * @return none
 */
void sendString(char *data);

#endif
