/**
 * @file 		uart.c 
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
#include "uart.h"

/**
 * @brief	 Function to initialize UART with BAUDRATE value
 * 
 * @param none
 * @return none 
 */
void USART_Init(){
    //set baudrate
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;

    //enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    //set frame fornat: 8-bit data
    UCSR0C = (3 << UCSZ00);
}

/**
 * @brief	 Function to transmit a single 8-bit value over UART
 * 
 * @param data -> Character to be transmitted
 * @return none
 */
void USART_Transmit(unsigned char data){
    // wait for empty transmit buffer
    while(!(UCSR0A & (1 << UDRE0)));

    // put data into the buffer, sends the data
    UDR0 = data;
}

/**
 * @brief	 Function to receive a single 8-bit value over UART
 * 
 * @param none
 * @return unsigned char -> character received
 */
unsigned char USART_Receive(void){
    //wait for data to be received
    while(!(UCSR0A & (1 << RXC0)));

    //Get and return received data from buffer
    return UDR0;
    
}

/**
 * @brief	 Function to send a string of characters over UART
 *          The string is terminated with \r\n
 * 
 * @param data -> pointer to character-string
 * @return none
 */
void sendString(char *data){
    while(*data){
        USART_Transmit(*data);
        data++;
    }
    USART_Transmit('\r');
    USART_Transmit('\n');
    
}