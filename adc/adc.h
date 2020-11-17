
#ifndef ADC_H
#define ADC_H

#include "../global_defs.h"

// Set up ADC with AVCC as ref and 128 prescaler
// @param: -
// return: -
void setupADC();

// Read ADC value from an ADC channel
// param: channel (ADC channel to read from)
// return: 16 bit ADC value
int16_t readADC(uint8_t channel);

#endif