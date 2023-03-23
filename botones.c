/*
 * Botones.c
 *
 * Created: 25/07/2018 03:01:52 a.m.
 *  Author: Andres
 */ 

#include "botones.h" 
#include "stdutils.h"
#include "rtc_ds1307.h"
#include "interrupts.h"
#include "display.h"
#include "atc24.h"
#include "WT588D.h"
#include "delay.h"

void Lee_Botones(void)
{	
unsigned char tmp_2;

////**************************************************////
////Boton Arriba Hora/Fcha****************************////
tmp_2=PORT_IN_BTNS;
tmp_2 &= BTN_UP_D;


if(ESTADO.ON_OFF==TRUE)
{	

 if((BOUTONS_PILOTES.boton_num[BTN_ARRIBA_CONFIG]& BTN_UP_D) != tmp_2)
  {
	if(MODE_DEPLOYE.selectionner_mode!=NO_PRG)
	{		
	
	BOUTONS_PILOTES.boton_top_hd=TRUE;	
	if(MODE_DEPLOYE.selectionner_mode!=PRG_ALRM_ON_OFF)
	on_audio(SOUND_MOVE_SETTINGS);
	
	
	}
	
	else// si esta en modo no prog, sube el brillo
	{
		 switch (BOUTONS_PILOTES.briller_change)
		 {
			 case BRILLO1:
			 BOUTONS_PILOTES.briller_change=BRILLO2;
			 EEWriteByte(SAVE_BRG,2);
			 break;
			 case BRILLO2:
			 BOUTONS_PILOTES.briller_change=BRILLO3;
			 EEWriteByte(SAVE_BRG,3);
			 break;
			 case BRILLO3:
			 BOUTONS_PILOTES.briller_change=BRILLO4;
			 EEWriteByte(SAVE_BRG,4);
			 break;
			 case BRILLO4:
			 BOUTONS_PILOTES.briller_change=BRILLO1;
			 EEWriteByte(SAVE_BRG,1);
			 break;
		 }
		 on_audio(SOUND_BRILLO);
	}
	
	BOUTONS_PILOTES.boton_num[BTN_ARRIBA_CONFIG]=PORT_IN_BTNS;
}


//***********************************************//
//Boton abajo hora*******************************//
tmp_2=PORT_IN_BTNS;
tmp_2 &= BTN_DWN_D;

if((BOUTONS_PILOTES.boton_num[BTN_ABAJO_CONFIG]& BTN_DWN_D)!=tmp_2)
{
	
	
	
   if(MODE_DEPLOYE.selectionner_mode != NO_PRG)
   {
	   	   
	BOUTONS_PILOTES.boton_dessous_hd=TRUE;   
	if(MODE_DEPLOYE.selectionner_mode!=PRG_ALRM_ON_OFF)
	on_audio(SOUND_MOVE_SETTINGS);
	   
   }	
  
 
   BOUTONS_PILOTES.boton_num[BTN_ABAJO_CONFIG]=PORT_IN_BTNS;
   
}
/*****************************************************/////
//*****************Boton Config Hora-Fecha*************//////

tmp_2=PORT_IN_BTNS;
tmp_2 &= BTN_PRG;


if((BOUTONS_PILOTES.boton_num[BTN_CONFIG_CLOCK] &  BTN_PRG)!=tmp_2)//si boton guardado es diferente al leido del puerto
{
	if(MODE_DEPLOYE.selectionner_mode<PRG_ALRM_SEG)
	MODE_DEPLOYE.selectionner_mode++;
/************** Salva Hora despues de que se colocan las horas****************//////

	if(MODE_DEPLOYE.selectionner_mode== PRG_MTH)// Programa Hora en RTC
	{
		DS1307_settime(DecimalToBCD(Maneja_tiempo.hour_prog),DecimalToBCD(Maneja_tiempo.min_prog),DecimalToBCD(Maneja_tiempo.sec_prog));
	}
/**************************************************************************************///

/***************Salva Fecha despues de colocar año*********************//////////

if(MODE_DEPLOYE.selectionner_mode==PRG_Ovrrd)
{
	DS1307_setdate(DecimalToBCD(Maneja_tiempo.date_prog),DecimalToBCD(Maneja_tiempo.month_prog),DecimalToBCD(Maneja_tiempo.year_prog));	
}

	
/*********Regresa a Mostrar Hora-(fecha) despues de programar****************/////	
	if(MODE_DEPLOYE.selectionner_mode==PRG_Ovrrd)
	MODE_DEPLOYE.selectionner_mode=NO_PRG;
	
	BOUTONS_PILOTES.boton_num[BTN_CONFIG_CLOCK]=PORT_IN_BTNS;	//actualiza estado de boton "config date"
	
//}
	//******************No Prog******************************************************////
/*	if(MODE_DEPLOYE.selectionner_mode==NO_PRG)
	{
		
	}*/
	//*****************************Programar Segundos********************************///
	if(MODE_DEPLOYE.selectionner_mode==PRG_SEG)
	{
	
	Maneja_tiempo.sec_prog  = PILOTE_HORLOGE.sec;
	Maneja_tiempo.min_prog  = PILOTE_HORLOGE.min;
	Maneja_tiempo.hour_prog = PILOTE_HORLOGE.hour;
	
	PILOTE_HORLOGE.past_sec = Maneja_tiempo.sec_prog+1;
	
	
	}
	
	//*****************************Programar Minutos******************************/////
	if(MODE_DEPLOYE.selectionner_mode==PRG_MIN)
	{

	PILOTE_HORLOGE.past_min = Maneja_tiempo.min_prog+1;	
	
	PILOTE_HORLOGE.min=Maneja_tiempo.min_prog;
	PILOTE_HORLOGE.sec=Maneja_tiempo.sec_prog;
	
	}
	
	//*****************************Programar Horas***********************************////
	if(MODE_DEPLOYE.selectionner_mode==PRG_HR)
	{
	
	PILOTE_HORLOGE.hour=Maneja_tiempo.hour_prog;
	PILOTE_HORLOGE.min=Maneja_tiempo.min_prog;
	PILOTE_HORLOGE.past_hour = Maneja_tiempo.hour_prog+1;
	}
	//****************************Pogramar Mes************************************//////

	if(MODE_DEPLOYE.selectionner_mode==PRG_MTH)
	{
	
		Maneja_tiempo.month_prog = PILOTE_HORLOGE.month;
	
		Maneja_tiempo.date_prog = PILOTE_HORLOGE.date;
		
		Maneja_tiempo.year_prog = PILOTE_HORLOGE.year;
		
		PILOTE_HORLOGE.past_month = Maneja_tiempo.month_prog+1;
		
	}
	
	if(MODE_DEPLOYE.selectionner_mode== PRG_DAY)
	{
		
			PILOTE_HORLOGE.past_date = Maneja_tiempo.date_prog+1;
			
			
			PILOTE_HORLOGE.date=Maneja_tiempo.date_prog;
			PILOTE_HORLOGE.year=Maneja_tiempo.year_prog;
			
		
	}
	
	
	if(MODE_DEPLOYE.selectionner_mode== PRG_YR)
	{
		PILOTE_HORLOGE.past_year=Maneja_tiempo.year_prog;
		
		PILOTE_HORLOGE.year=Maneja_tiempo.year_prog;
		PILOTE_HORLOGE.date=Maneja_tiempo.date_prog;
		
		
	}
	
	if(MODE_DEPLOYE.selectionner_mode!= NO_PRG)
	{
		//poner condicion para que no suene estando en modo programacion de alarma
	 if(MODE_DEPLOYE.selectionner_mode<PRG_Ovrrd)
		on_audio(SOUND_ENTER_SETTINGS);
		
	 
		
	}
	
	if(MODE_DEPLOYE.selectionner_mode== NO_PRG)
	{
		on_audio(SOUND_MENU_CLOSE);
	}	
	
	
}

/******************************************************/
/**********Boton Programa Alarma*******************///
/*************************************************/////

tmp_2= PORT_IN_BTNS & BTN_ALARM ;

if((BOUTONS_PILOTES.boton_num[BTN_ALARMA]&BTN_ALARM) != tmp_2)
{
	BOUTONS_PILOTES.boton_num[BTN_ALARMA]=PORT_IN_BTNS;
	
	switch (MODE_DEPLOYE.selectionner_mode)
	{
		
	
	case NO_PRG:		
	
	 if((PORT_IN_BUSY & BUSY_WT588)==Mask_BIT2)
		{
			Execute_audio(SOUND_STOP);
				
		}
	else
	{
		MODE_DEPLOYE.selectionner_mode=PRG_ALRM_MIN;//min
		
		Drive_Alarm.sv_rd_sec_alrm_aadr=SAVE_ALRM_ON_OFF;
		Drive_Alarm.sv_rd_min_alrm_aadr=SAVE_ALRM_MIN;
		Drive_Alarm.sv_rd_hour_alrm_aadr=SAVE_ALRM_HR;
		
		
		PILOTE_HORLOGE.sec=EEReadByte(Drive_Alarm.sv_rd_sec_alrm_aadr);
		DELAY_us(800);
		PILOTE_HORLOGE.min= EEReadByte(Drive_Alarm.sv_rd_min_alrm_aadr);
		
		DELAY_us(800);
		PILOTE_HORLOGE.hour= EEReadByte(Drive_Alarm.sv_rd_hour_alrm_aadr);
		
		DELAY_us(800);
		
		PILOTE_HORLOGE.alrm_sec=PILOTE_HORLOGE.sec;		
		PILOTE_HORLOGE.alrm_min=PILOTE_HORLOGE.min;
		PILOTE_HORLOGE.alrm_hr =PILOTE_HORLOGE.hour;
		
	}
	
	break;
		
	case PRG_ALRM_SEG:
	
	MODE_DEPLOYE.selectionner_mode++;
		
	PILOTE_HORLOGE.past_sec_alrm = PILOTE_HORLOGE.sec+1;
	
	PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
	PILOTE_HORLOGE.hour=PILOTE_HORLOGE.alrm_hr;
	
	break;
	
	case PRG_ALRM_MIN:
	
	
		
		MODE_DEPLOYE.selectionner_mode++;
		//PILOTE_HORLOGE.min= EEReadByte(SAVE_ALRM_MIN);
		
		PILOTE_HORLOGE.past_min_alrm = PILOTE_HORLOGE.alrm_min+1;
		
		PILOTE_HORLOGE.min=PILOTE_HORLOGE.alrm_min;
		PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
		PILOTE_HORLOGE.hour=PILOTE_HORLOGE.alrm_hr;
		
		
		break;	
			
	case PRG_ALRM_HR:
			
			MODE_DEPLOYE.selectionner_mode=NO_PRG;
			
			
			PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
			PILOTE_HORLOGE.hour=PILOTE_HORLOGE.alrm_hr;
			PILOTE_HORLOGE.min=PILOTE_HORLOGE.alrm_min;
			
			PILOTE_HORLOGE.past_hour_alrm = PILOTE_HORLOGE.alrm_hr+1;
			
			//write2bytes
			EEWrite2Bytes(SAVE_ALRM_MIN,PILOTE_HORLOGE.alrm_min,PILOTE_HORLOGE.alrm_hr);//solo escribe min y hr
			
			//if(On_Off_Options.alarm==TRUE)
		//	on_audio_alrm(PILOTE_HORLOGE.Alarm_PlayList);
			LeeRTC();
			break;
			
	case PRG_ALRM_ON_OFF:
			MODE_DEPLOYE.selectionner_mode=NO_PRG;
			
			PILOTE_HORLOGE.past_sec_alrm = PILOTE_HORLOGE.alrm_sec+1;
			EEWriteByte(SAVE_ALRM_ON_OFF, PILOTE_HORLOGE.alrm_sec);//Esta salvando si esta activa la alarma o desactiva
		
			
			Execute_audio(SOUND_STOP);
			
			
			
			break;
	
			
		}
	
}


/***************************************////
/******Boton Mostrar Alarma On-off*///////////////
/****************************************/

tmp_2=PORT_IN_BTNS & BTN_SHW_ALRM;




if((BOUTONS_PILOTES.boton_num[BTN_SHOW_ALARM]&BTN_SHW_ALRM) != tmp_2)
{
	BOUTONS_PILOTES.boton_num[BTN_SHOW_ALARM]=PORT_IN_BTNS;
	
	/*  aqui  */
	
	if(MODE_DEPLOYE.selectionner_mode==NO_PRG)
	{
		if((PORT_IN_BUSY & BUSY_WT588)==Mask_BIT2)
		{
			
			Execute_audio(SOUND_STOP);
		}
		else
		{
			
			switch(KIND_DISPLAY.show_date)
			
			{
				
				case ALARM:
				
				if(MODE_DEPLOYE.selectionner_mode==NO_PRG)
				{
					MODE_DEPLOYE.selectionner_mode=PRG_ALRM_ON_OFF;
					KIND_DISPLAY.show_date=CLOCK;
					on_audio_alrm(PILOTE_HORLOGE.Alarm_PlayList);
					PILOTE_HORLOGE.sec=EEReadByte(SAVE_ALRM_ON_OFF);
					PILOTE_HORLOGE.alrm_sec=PILOTE_HORLOGE.sec;
					
				}
				else
				{
					MODE_DEPLOYE.selectionner_mode=NO_PRG;
					EEWriteByte(SAVE_ALRM_ON_OFF,PILOTE_HORLOGE.alrm_sec);
					KIND_DISPLAY.show_date=CLOCK;
					
					Execute_audio(SOUND_STOP);
					PILOTE_HORLOGE.lee_RTC=TRUE;
					LeeRTC();
					
				}
				KIND_DISPLAY.show_count=0;
				break;
				
				case CLOCK:
				KIND_DISPLAY.show_date=ALARM;
				//  On_Off_Options.alarm=FALSE;
				break;
				
			}
			
		}
		
	}
	else
	{
		switch(KIND_DISPLAY.show_date)
		
		{
			
			case ALARM:
			
			if(MODE_DEPLOYE.selectionner_mode==NO_PRG)
			{
				MODE_DEPLOYE.selectionner_mode=PRG_ALRM_ON_OFF;
				KIND_DISPLAY.show_date=CLOCK;
				on_audio_alrm(PILOTE_HORLOGE.Alarm_PlayList);
				PILOTE_HORLOGE.sec=EEReadByte(SAVE_ALRM_ON_OFF);
				PILOTE_HORLOGE.alrm_sec=PILOTE_HORLOGE.sec;
				
			}
			else
			{
				MODE_DEPLOYE.selectionner_mode=NO_PRG;
				EEWriteByte(SAVE_ALRM_ON_OFF,PILOTE_HORLOGE.alrm_sec);
				KIND_DISPLAY.show_date=CLOCK;
				
				Execute_audio(SOUND_STOP);
				PILOTE_HORLOGE.lee_RTC=TRUE;
				LeeRTC();
				
			}
			KIND_DISPLAY.show_count=0;
			break;
			
			case CLOCK:
			KIND_DISPLAY.show_date=ALARM;
			//  On_Off_Options.alarm=FALSE;
			break;
			
		}
	}



}

 

/******************************************/
/*******Boton mostrar fecha**************///
/*****************************************/

tmp_2=PIN_BTN5  & BTN_MSK_SWDATE;

if((BOUTONS_PILOTES.boton_num[BTN_SHOW_DATE]&BTN_MSK_SWDATE) != tmp_2)
{
BOUTONS_PILOTES.boton_num[BTN_SHOW_DATE]=PIN_BTN5;

 switch(KIND_DISPLAY.show_date)
 
 {
	 
	 case CLOCK:
	 KIND_DISPLAY.show_date=CALENDAR;
	 break;
	 case CALENDAR:
	 KIND_DISPLAY.show_date=CLOCK;
	 KIND_DISPLAY.show_count=0;
	 break;
	 
	 
 }
 
}

/***************************************************/
/******Boton Muestra apaga Alarma/sonidos**********/
/*********************************************/////

tmp_2= PORT_IN_BTNS  & BTN_CNF_SONIDOS ;

if((BOUTONS_PILOTES.boton_num[BTN_CNF_SOUND]&BTN_CNF_SONIDOS) != tmp_2)
{
	BOUTONS_PILOTES.boton_num[BTN_CNF_SOUND]= PORT_IN_BTNS;	
	
	
	  switch (MODE_DEPLOYE.selectionner_mode)
	  {
		  
	  case NO_PRG:
	  MODE_DEPLOYE.selectionner_mode=PRG_SONIDOS;   	  
	  on_audio(SOUND_FANFARE);
		break;	 
	  case PRG_SONIDOS:
	  MODE_DEPLOYE.selectionner_mode=PRG_TIPO_ALARMA;
	  Execute_audio(PILOTE_HORLOGE.Alarm_PlayList);	 
	  break;
	  case PRG_TIPO_ALARMA:
	  MODE_DEPLOYE.selectionner_mode=NO_PRG;
	  Execute_audio(SOUND_STOP);
	  PILOTE_HORLOGE.lee_RTC=TRUE;
	  LeeRTC();
	  break;	  
	 /*
	  case PRG_VOLUMEN:
	  MODE_DEPLOYE.selectionner_mode=NO_PRG;
	  PILOTE_HORLOGE.lee_RTC=TRUE;
	  LeeRTC();
	  break;	  
	*/  
	  }
	
	
     } 

	}
	
	
	/****************************************/
/**********Boton On Off**************////
/*************************************/
tmp_2=PORT_IN_BTNS;
tmp_2 &= BTN_ON_OFF;

if((BOUTONS_PILOTES.boton_num[BTN_PRENDE_APAGA]&BTN_ON_OFF)!=tmp_2)
{
	
	switch(ESTADO.ON_OFF)
	{
		case FALSE:
		
		ESTADO.ON_OFF=TRUE;
		DDRD |=(1<<PD5);

		TCCR1A= (1<<COM1A1) | (1<<COM1A0) | (1<<WGM11) | (1<<WGM10);
		TCCR1B= (1<<WGM12)  | (1<<CS10);
    BOUTONS_PILOTES.boton_num[0]=PORT_IN_BTNS ;
	BOUTONS_PILOTES.boton_num[1]=PORT_IN_BTNS ;
	BOUTONS_PILOTES.boton_num[2]=PORT_IN_BTNS;
	BOUTONS_PILOTES.boton_num[3]=PORT_IN_BTNS;
	BOUTONS_PILOTES.boton_num[4]=PORT_IN_BTNS;
	/******************************************************////
	BOUTONS_PILOTES.boton_num[5]=PIN_BTN5     ;//****PD5 OC1A (PWM) y va al OE del 595 asi que le asignamos PA3 al boton 5
	/********************************************************/////
	BOUTONS_PILOTES.boton_num[6]=PORT_IN_BTNS ;
	BOUTONS_PILOTES.boton_num[7]=PORT_IN_BTNS ;
	break;
	
        case TRUE:
 
		ESTADO.ON_OFF=FALSE;
		
	
	TCCR1A=0; //(~(1<<COM1A1)) | (~(1<<COM1A0)) | (~(1<<WGM11)) | (~(1<<WGM10)) ;
	TCCR1B=0;//(~(1<<WGM12))  | (~(1<<CS10));
	
	
		PORTD |= (1<<PD5);

	break;

	}
	
		BOUTONS_PILOTES.boton_num[BTN_PRENDE_APAGA]=PORT_IN_BTNS;
	
    }


 

}