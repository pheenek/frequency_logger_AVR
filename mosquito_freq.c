/**
 * @file 		mosquito_freq.c 
 * 
 * @author 		Stephen Kairu (kairu@pheenek.com) 
 * 
 * @brief	 	This file contains a program that collects data over the ADC
 * 				channels, converts the data into the frequency domain, and transmits
 * 				it throught the UART
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

#include "global_defs.h"
#include "adc/adc.h"
#include "uart/uart.h"
#include "ffft/ffft.h"

#define MIC PC0

/**
 * @brief	 Function to capture analog data from the microphone
 * 
 * @param buffer -> Buffer where data is placed
 * @param count -> Number of raw data values to be captured
 */
void capture_wave(int16_t *buffer, uint16_t count) {
	ADMUX = _BV(REFS0)|_BV(ADLAR); //channel

	do {
		ADCSRA = _BV(ADEN)|_BV(ADSC)|_BV(ADIF)|_BV(ADPS2)|_BV(ADPS1);
		while (bit_is_clear(ADCSRA, ADIF));
		*buffer++ = ADC - 32768;
		_delay_us(192); // Reduce sampling frequency to 4KHz from 18Khz
	} while (--count);
	ADCSRA = 0;
}

/**
 * @brief	 Program entry point
 * 
 * @return int 
 */
int main() {
	// TCCR1B = _BV(CS10) | _BV(CS11);

	/**
	 * FFT variables
	 */
	// uint16_t t1;
	int16_t capture[FFT_N];
	complex_t bfly_buff[FFT_N];
	uint16_t spectrum_buf[FFT_N/2];
	
	uint16_t n, s;
	char tempBuf[16];

	uint16_t degBuf[2];
	uint16_t result;

	// Initialize ADC
	setupADC();

	// Initialize USART communication interface
	USART_Init();

	while (1) {
		/* Simulation of temperature data ----------*/
		setupADC();
		degBuf[0] = readADC(1)*0.00763;
		degBuf[1] = readADC(2)*0.00763;
		result = (degBuf[0]+degBuf[1])/2;

		
		/* Capturing of sound wave------------------------*/
		// TCNT1 = 0;
		capture_wave(capture, FFT_N);
		// t1 = TCNT1;
		fft_input(capture, bfly_buff);
		fft_execute(bfly_buff);
		fft_output(bfly_buff, spectrum_buf);
		
		/*Transmission of frequency data through USART-------*/
		for (n = 0; n < FFT_N/2; n++) {
			s = spectrum_buf[n];
			memset(tempBuf, '\0', sizeof(tempBuf));
			sprintf(tempBuf, "%u", s);
			char *p = tempBuf;
			while (*p) {
				USART_Transmit(*p);
				p++;
			}
			USART_Transmit(',');
		}

		/*Transmission of temp through USART-------*/
		s = result;
		memset(tempBuf, '\0', sizeof(tempBuf));
		sprintf(tempBuf, "%u", s);
		char *p = tempBuf;
		while (*p) {
			USART_Transmit(*p);
			p++;
		}
		USART_Transmit('\n');
		
		
		// memset(data, '\0', sizeof(data));
		// sprintf(data, "%d samples in %u clocks", (int)FFT_N, t1);
		// sendString(data);
	}
}
