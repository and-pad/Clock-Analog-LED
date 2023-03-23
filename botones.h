/*
 * IncFile1.h
 *
 * Created: 25/07/2018 02:58:38 a.m.
 *  Author: Andres
 */ 


#ifndef BOTONES_H_
#define BOTONES_H_

#include <avr/io.h>
#include "stdutils.h"
#define DDR_BOTONES DDRD
#define PORT_BOTONES PORTD

#define DDR_BTN5 DDRA
#define PORT_BTN5 PORTA
#define PIN_BTN5 PINA

#define PORT_IN_BTNS PIND



//#define BTN_PRG_SAVE (PORT_BOTONES & BTN_PRG)
/***Define la posicion en el puerto de los botones)****////
#define BTN_UP_D       Mask_BIT0
#define BTN_DWN_D      Mask_BIT1
#define BTN_PRG        Mask_BIT2
#define BTN_ALARM      Mask_BIT3

#define BTN_ON_OFF     Mask_BIT4

#define BTN_MSK_SWDATE  Mask_BIT3  //PA3

#define BTN_CNF_SONIDOS  Mask_BIT6
#define BTN_SHW_ALRM   Mask_BIT7
 

//*****desplegado*********////
#define CLOCK    0
#define CALENDAR 1
#define ALARM    2


/****Define la posicion de apuntador para boton****/////
#define BTN_ARRIBA_CONFIG 0
#define BTN_ABAJO_CONFIG  1
#define BTN_CONFIG_CLOCK  2
#define BTN_ALARMA        3

#define BTN_PRENDE_APAGA  4
#define BTN_SHOW_DATE     5
#define BTN_CNF_SOUND     6
#define BTN_SHOW_ALARM    7   



#define NO_PRG  0
#define PRG_SEG 1
#define PRG_MIN 2
#define PRG_HR  3
#define PRG_MTH 4
#define PRG_DAY 5
#define PRG_YR  6
#define PRG_Ovrrd 7
 
#define PRG_ALRM_SEG    8
#define PRG_ALRM_MIN    9
#define PRG_ALRM_HR     10
#define PRG_ALRM_ON_OFF 11
#define PRG_ALRM_Ovvd   12

#define PRG_SONIDOS     13
#define PRG_TIPO_ALARMA 14
#define PRG_VOLUMEN     15

#define BRILLO1 60
#define BRILLO2 341
#define BRILLO3	682
#define BRILLO4 1023


typedef volatile struct  
{
	uint8_t boton_num[8];//
	uint8_t boton_top_hd;
	uint8_t boton_dessous_hd;
	uint16_t boton_briller;
	uint16_t briller_change;
	
	
	
}Botones;



typedef struct 
{
   uint8_t 	selectionner_mode;
  // uint8_t  prendre_temps;
   
}MODO;

typedef struct
{
	uint8_t ON_OFF;
	
}PRINCIPAL;

PRINCIPAL ESTADO;

MODO    MODE_DEPLOYE;
Botones BOUTONS_PILOTES;

/****Prototipos botones**********/
void Lee_Botones(void);

#endif /* INCFILE1_H_ */