/*
 * IncFile1.h
 *
 * Created: 25/07/2018 06:25:26 p.m.
 *  Author: Andres
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "delay.h"



typedef struct{ 
uint8_t sec_prog;
uint8_t min_prog;
uint8_t hour_prog;
uint8_t month_prog; 
uint8_t date_prog;
uint8_t year_prog;
}Drive;

Drive Maneja_tiempo;


typedef struct{
uint8_t show_date;
uint16_t show_count;	
uint16_t show_count_calendar;
	
}KIND ;

KIND KIND_DISPLAY;

void Mode_de_DEPLOYE (void);

#endif /* INCFILE1_H_ */