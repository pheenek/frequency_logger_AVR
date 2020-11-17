
#include "adc.h"

void setupADC(){
    // Set up ADC
    /* reference voltage on AVCC */
    ADMUX |= (1 << REFS0);
    /* ADC clock prescaler /128 */
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    /* enable ADC */
    ADCSRA |= (1 << ADEN);
}

int16_t readADC(uint8_t channel) {
    ADMUX = (0xf0 & ADMUX) | channel;
    ADCSRA |= (1 << ADSC);
    loop_until_bit_is_clear(ADCSRA, ADSC);
    return (ADC);
}

