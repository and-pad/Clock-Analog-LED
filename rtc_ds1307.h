/*
 * rtc_ds1307.h
 *
 * Created: 08/05/2018 12:32:00 p.m.
 *  Author: Andres
 */ 
#ifndef RTC_DS1307_H_
#define RTC_DS1307_H_

#define F_CPU 16000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>								/* Include AVR std. library file */
#include <util/delay.h>							/* Include inbuilt defined Delay header file */
#include <math.h>

#include <avr/pgmspace.h>

#define DS1307_write 0xD0
#define DS1307_read 0xD1
/***definiciones del RTC*/////
#define SEC   0x00
#define MIN   0x01
#define HOUR  0x02
#define DAY   0x03
#define DATE  0x04
#define MONTH 0X05
#define YEAR  0x06
/******************************////

/****definiciones de calendario para RTC************///////
#define ENE  1
#define FEB  2
#define MAR  3
#define ABR  4
#define MAY2 5 
#define JUN  6
#define JUL  7
#define AGO2 8 
#define SEP2 9
#define OCT  10
#define NOV  11
#define DIC  12
/***********///////////////*****************************///////
/***********variables para manejo del RTC************//////
typedef struct 
{

uint8_t sec;
uint8_t min; 
uint8_t hour;
uint8_t date;
uint8_t month;
uint8_t year;

uint8_t alrm_sec;
uint8_t alrm_min;
uint8_t alrm_hr;

//variables para verificar si cambio de estado y desplegar
uint8_t past_sec;
uint8_t past_min;
uint8_t past_hour;
uint8_t past_month;
uint8_t past_date;
uint8_t past_year;


uint8_t past_sec_alrm;
uint8_t past_min_alrm;
uint8_t past_hour_alrm;
//**********************************************************

uint8_t sound;
uint8_t knd_alarm;
uint8_t volumen;

uint8_t Alarm_PlayList;

uint8_t past_sound;
uint8_t past_knd_alarm;
uint8_t past_volumen;

uint8_t lee_RTC;


uint8_t take_time1;
uint16_t take_time2_Triforce;
uint8_t time_toogle;

uint8_t cortar_sonido;


}PILOTE_RTC;
/****************************************************////////

PILOTE_RTC PILOTE_HORLOGE;
/*********Prototipos para RTC************************///////
void DS1307_put(unsigned char addr, unsigned char dato );
unsigned char DS1307_get(unsigned char addr);
void DS1307_settime(unsigned char hh,unsigned char mm,unsigned char ss);
void DS1307_setdate(unsigned char dd, unsigned char mm, unsigned char yy);
/********************************************************///////
#endif /* rtc_ds1307_H_ */