

#include "global_defs.h"
#define MIC PC0

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

int main() {
	// TCCR1B = _BV(CS10) | _BV(CS11);

	// uint16_t t1;
	int16_t capture[FFT_N];
	complex_t bfly_buff[FFT_N];
	uint16_t spectrum_buf[FFT_N/2];
	
	uint16_t n, s;
	char tempBuf[16];

	uint16_t degBuf[2];
	uint16_t result;

	setupADC();
	USART_Init();

	while (1) {
		/* Reading and calculation of temperature----------*/
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
		
		/*Transmission of fft through USART-------*/
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
