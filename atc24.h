/*
 * ATC24.h
 *
 * Created: 13/08/2018 04:41:57 p.m.
 *  Author: Andres
 */ 


#ifndef ATC24_H_
#define ATC24_H_

#include "i2c.h"

#define ADDR_24C32 0xA0
#define HORAS 1
#define MINUTOS 2
#define SEGUNDOS 3


#define SAVE_BRG                       0
#define SAVE_ALRM_ON_OFF    0x0001
#define SAVE_ALRM_MIN           0x0002
#define SAVE_ALRM_HR             0x0003
#define SAVE_KIND_ALARM      0x0004
#define SAVE_SOUND_STATE   0x0005
#define SAVE_VOLUMEN            0x0006

#define BRG1 1
#define BRG2 2
#define BRG3 3
#define BRG4 4

typedef struct  
{
 uint16_t	sv_rd_sec_alrm_aadr:SAVE_ALRM_ON_OFF;
  uint16_t	sv_rd_min_alrm_aadr:SAVE_ALRM_MIN;
  uint16_t	sv_rd_hour_alrm_aadr:SAVE_ALRM_HR;
}ALARMA;


ALARMA Drive_Alarm;

/*****prototipos****////
//void EEOpen(void);
void EEWriteByte(uint16_t address,uint8_t data);
void EEWrite2Bytes(uint16_t address,uint8_t data1, uint8_t data2);
uint8_t EEReadByte(uint16_t address);


#endif /* ATC24_H_ */