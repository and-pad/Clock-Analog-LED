/*
 * _24C32.h
 *
 * Created: 13/08/2018 02:55:46 p.m.
 *  Author: Andres
 */ 


#ifndef 24C32_H_
#define 24C32_H_

#include <avr/io.h>

#include "stdutils.h"

#define C32DEV 0b1010
#define HORAS 3
#define MINUTOS 4
#define SEGUNDOS 5


void eewrite(uint8_t device, uint16_t addr, uint8_t dat);
void eeread(uint8_t device, uint16_t addr);



#endif /* 24C32_H_ */