/*
 * _24C32.c
 *
 * Created: 13/08/2018 02:54:42 p.m.
 *  Author: Andres
 */ 


#include "24C32.h"
#include <avr/io.h>
#include "i2c.h"
#include <util/twi.h>
#include "stdutils.h"


//******************************************************************
//Function  : To write single byte into EEPROM memory.
//Arguments : 1. SLA_W device address.
//          : 2. 16 bit internal address of the location to be written.
//          : 3. One byte of data to be written into EEPROM.
//Return    :    none
//******************************************************************


	void eewrite(uint8_t device, uint16_t addr, uint8_t dat)
	{
		while(1)
		{
			I2C_Start();
			I2C_Write(device);
			
			if ( (TWSR & 0xF8) != TW_MT_SLA_NACK) break;
			
			I2C_Stop();
		}

		I2C_Write(addr >> 8);
	    I2C_Write(addr);

		I2C_Write(dat);
		I2C_Stop();
	}
	
	uint8_t eeread(uint8_t device, uint16_t addr)
	{
		uint8_t dat;
		
		while(1)
		{
			I2C_Start();
			I2C_Write(device);
			
			if ( (TWSR & 0xF8) != TW_MT_SLA_NACK) break;
			
			I2C_Stop();
		}
		
	    I2C_Write(addr >> 8);
	    I2C_Write(addr);

		I2C_Start();
		I2C_Write(device+1);
		//dat = twiread(0); //0 - NOACK
		dat = I2C_Read(0);
		I2C_Stop();
		
		return dat;
	}