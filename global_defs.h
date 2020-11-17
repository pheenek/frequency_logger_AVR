
#ifndef F_CPU
#define F_CPU 16000000UL    // define the processor frequency clock at 16MHz
#endif

#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "adc/adc.h"
#include "uart/uart.h"
#include "ffft/ffft.h"
