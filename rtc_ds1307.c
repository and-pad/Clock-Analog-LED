/*
 *RTC_DS1307.cpp
 *
 * Created: 08/05/2018 11:27:58 a.m.
 *  Author: Andres Padilla
 * Lee y escribe en el DS1307
 */ 

#include "rtc_ds1307.h"
#include "i2c.h"

//#define F_CPU 16000000UL							/* Define CPU clock Frequency e.g. here its 8MHz */
#include <avr/io.h>								/* Include AVR std. library file */
#include <util/delay.h>							/* Include inbuilt defined Delay header file */
#include <math.h>

#include <avr/pgmspace.h>

void DS1307_put(unsigned char addr, unsigned char dato )
{
	//I2C_Init();
    I2C_Start();
	I2C_Write(dato);
	I2C_Stop();
	 	
}

unsigned char DS1307_get(unsigned char addr)
{
	unsigned char ret;	
	
 	I2C_Start(); //avisa al bus
	I2C_Write(DS1307_write);// dirije al chip
	I2C_Write(addr);        // le dice que direccion queremos leer	
	
	I2C_Start(); //le dice que vamos a leer
    I2C_Write(DS1307_read);	
	ret = I2C_Read(0);		      
	I2C_Stop();                     //libera i2c
	return ret;
	
}


void DS1307_settime(unsigned char hh,unsigned char mm,unsigned char ss)
{
	
	I2C_Start(); //avisa a ds1307
	I2C_Write(DS1307_write);         //inicia desde segundos
	I2C_Write(SEC);
	
	I2C_Write(ss);
	I2C_Write(mm);
	I2C_Write(hh);
	
	I2C_Stop();	
	
}

void DS1307_setdate(unsigned char dd, unsigned char mm, unsigned char yy)
{
	I2C_Start();
	I2C_Write(DS1307_write); //avisa a ds1307
	I2C_Write(DATE);         //inicia desde fecha
	
	I2C_Write(dd);
	I2C_Write(mm);
	I2C_Write(yy);
	
	I2C_Stop();
}