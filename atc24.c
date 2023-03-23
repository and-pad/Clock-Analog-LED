/*
 * ATC24.c
 *
 * Created: 13/08/2018 04:41:26 p.m.
 *  Author: Andres
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "atc24.h"
//#include "rtc_ds1307.h"
#include "interrupts.h"
#include "delay.h"

void EEWrite2Bytes(uint16_t address,uint8_t data1, uint8_t data2)
{
	//uint8_t check;
	I2C_Start();
	I2C_Write(0xA0);//direccion EEprom A0	
	I2C_Write(address>>8);        // escribimos bit alto de la direccion que queremos leer	
	I2C_Write(address);           //""""""""""""""""bajo"""""""""""""""""""""""""""""""""	
  //  I2C_Write(data1);
	I2C_Write(data1);
	I2C_Write(data2);	
	I2C_Stop();
	                     //libera i2c
	
	

}

void EEWriteByte(uint16_t address,uint8_t data)
{
	//uint8_t check;
	I2C_Start();
	I2C_Write(0xA0);//direccion EEprom A0
	I2C_Write(address>>8);        // escribimos bit alto de la direccion que queremos leer
	I2C_Write(address);           //""""""""""""""""bajo"""""""""""""""""""""""""""""""""
	I2C_Write(data);
	
	I2C_Stop();
	//libera i2c
	
	

}

uint8_t EEReadByte(uint16_t addds)
{
	unsigned char ret;
	uint16_t check;
	
	I2C_Start(); //avisa al bus	
	I2C_Write(0xA0);// dirije al chip
    check = addds >>8; //escribe byte alto 
	I2C_Write(check);	
	I2C_Write(addds);// escribe byte bajo	
	I2C_Start(); // condicion de inicio de protocolo para comensar lectura	
	I2C_Write_RD(0b10100001); // codigo de lectura de protocolo	
	ret = I2C_Read(0);// lectura
	
	I2C_Stop();                     //libera i2c
	return ret;	
}

