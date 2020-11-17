
#include "uart.h"

// function to initialize UART
void USART_Init(){
    //set baudrate
    UBRR0H = (MYUBRR >> 8);
    UBRR0L = MYUBRR;

    //enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    //set frame fornat: 8 data
    UCSR0C = (3 << UCSZ00);
}

void USART_Transmit(unsigned char data){
    // wait for empty transmit buffer
    while(!(UCSR0A & (1 << UDRE0)));

    // put data into the buffer, sends the data
    UDR0 = data;
}

unsigned char USART_Receive(void){
    //wait for data to be received
    while(!(UCSR0A & (1 << RXC0)));

    //Get and return received data from buffer
    return UDR0;
    
}

void sendString(char *data){
    while(*data){
        USART_Transmit(*data);
        data++;
    }
    USART_Transmit('\r');
    USART_Transmit('\n');
    
}