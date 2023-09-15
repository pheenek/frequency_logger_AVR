/**
 * @file 		adc.c 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	    This files contains the implementations of some basic functions to
 *              set up and use the ADC on the ATMega328P microcontroller
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
#include "adc.h"

/**
 * @brief	 Set up the ADC with AVCC as ref and 128 prescaler
 * 
 * @param none
 * @return none
 */
void setupADC(void){
    // Set up ADC
    /* reference voltage on AVCC */
    ADMUX |= (1 << REFS0);
    /* ADC clock prescaler /128 */
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    /* enable ADC */
    ADCSRA |= (1 << ADEN);
}

/**
 * @brief	 Read ADC value from the ADC channel specified
 * 
 * @param channel -> ADC channel
 * @return int16_t -> 16-bit ADC value (10-bit resolution)
 */
int16_t readADC(uint8_t channel) {
    // Select the ADC channel provided
    ADMUX = (0xf0 & ADMUX) | channel;
    // Start a single ADC conversion
    ADCSRA |= (1 << ADSC);
    // Wait for the conversion to complete (bit cleared by hardware)
    loop_until_bit_is_clear(ADCSRA, ADSC);
    // Return ADC value acquired
    return (ADC);
}

