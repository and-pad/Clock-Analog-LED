/*
 * Display.c
 *
 * Created: 25/07/2018 04:08:23 p.m.
 *  Author: Andres
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "i2c.h"
#include "rtc_ds1307.h"
#include <util/delay.h>						/* Include inbuilt defined Delay header file */
//#include "delay.h"
#include <stdbool.h>
#include "interrupts.h"
#include "botones.h"
#include "stdutils.h"
#include "display.h"
#include "atc24.h"
#include "WT588D.h"

void Mode_de_DEPLOYE (void)
{	
	switch (MODE_DEPLOYE.selectionner_mode)
	{	
	case PRG_SEG:		
	if(BOUTONS_PILOTES.boton_top_hd)
	   {
		//****suma 1 segundo   
	   Maneja_tiempo.sec_prog++;
	   if(Maneja_tiempo.sec_prog>59/*segundos*/)	   
	   Maneja_tiempo.sec_prog=0;          // si llegó al limite superior de minutos se reinicia a 0 haciendo un bucle
	  //**********************************	  
	   BOUTONS_PILOTES.boton_top_hd=FALSE;
	   PILOTE_HORLOGE.sec=Maneja_tiempo.sec_prog;
	   }	
	   //********resta 1 segundo   
	if(BOUTONS_PILOTES.boton_dessous_hd)
	{
		Maneja_tiempo.sec_prog--;
		if(Maneja_tiempo.sec_prog==0xFF)/* segundos */
		Maneja_tiempo.sec_prog=59; //limite inferior, pasa a superior
		BOUTONS_PILOTES.boton_dessous_hd=FALSE;		
		PILOTE_HORLOGE.sec=Maneja_tiempo.sec_prog;//pasa a variable de mostrado
	}   
	
	//***********************parpadeo*******************/////////
	if(PILOTE_HORLOGE.time_toogle==FALSE)
	{
		PILOTE_HORLOGE.sec=0;//
		PILOTE_HORLOGE.past_sec= PILOTE_HORLOGE.sec+2;
		//Acomoda_5x32();
		
	}
	else
	{
		PILOTE_HORLOGE.sec=Maneja_tiempo.sec_prog;
		PILOTE_HORLOGE.past_sec=PILOTE_HORLOGE.sec+1;
		//Acomoda_5x32();
	}
	
	//PILOTE_HORLOGE.past_sec=PILOTE_HORLOGE.sec_prog;
	break;
	
	case PRG_MIN:
	
	if(BOUTONS_PILOTES.boton_top_hd)
	{	
	
	Maneja_tiempo.min_prog++;
	if (Maneja_tiempo.min_prog>59)
	Maneja_tiempo.min_prog=0;
	
	PILOTE_HORLOGE.min=Maneja_tiempo.min_prog;
	BOUTONS_PILOTES.boton_top_hd=FALSE;
		
	}
	
	
	if(BOUTONS_PILOTES.boton_dessous_hd)
	{
		Maneja_tiempo.min_prog--;
		if(Maneja_tiempo.min_prog==0xFF)
		Maneja_tiempo.min_prog=59;
		BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		PILOTE_HORLOGE.min=Maneja_tiempo.min_prog;
		
	}
//*******************parpadeo*****************	
	if(PILOTE_HORLOGE.time_toogle==FALSE)
	{
		PILOTE_HORLOGE.min=0;//programar en ACOMODA5x32(); un numero mayor al limite superior para mejor parpadeo donde se apague por completo
		
		PILOTE_HORLOGE.past_min= PILOTE_HORLOGE.min+2;
		//Acomoda_5x32();
		
	}
	else
	{
		PILOTE_HORLOGE.min=Maneja_tiempo.min_prog;
		PILOTE_HORLOGE.past_min=PILOTE_HORLOGE.min+1;
		//Acomoda_5x32();
	}
	
	break;
	
	case PRG_HR:	
	
	if(BOUTONS_PILOTES.boton_top_hd==TRUE)
	{
		Maneja_tiempo.hour_prog++;
		if(Maneja_tiempo.hour_prog>23)
		Maneja_tiempo.hour_prog=0;
		
		BOUTONS_PILOTES.boton_top_hd=FALSE;
        PILOTE_HORLOGE.hour=Maneja_tiempo.hour_prog;
			
	}
	
	if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	{
		Maneja_tiempo.hour_prog--;
		if(Maneja_tiempo.hour_prog==0xFF)
		Maneja_tiempo.hour_prog=23;
		
		BOUTONS_PILOTES.boton_dessous_hd=FALSE;
	    PILOTE_HORLOGE.hour=Maneja_tiempo.hour_prog;
		
	}
	
	if(PILOTE_HORLOGE.time_toogle==FALSE)
	{
		if(Maneja_tiempo.hour_prog!=11)
		PILOTE_HORLOGE.hour=0;
		else
		PILOTE_HORLOGE.hour=0;
		
		PILOTE_HORLOGE.past_hour= PILOTE_HORLOGE.hour+2;
		//Acomoda_5x32();
		
	}
	else
	{
		PILOTE_HORLOGE.hour=Maneja_tiempo.hour_prog;
		PILOTE_HORLOGE.past_hour=PILOTE_HORLOGE.hour+1;
		//Acomoda_5x32();
	}
	
	
	break;
	
	case PRG_MTH:
	
	if(BOUTONS_PILOTES.boton_top_hd==TRUE)
	{
		Maneja_tiempo.month_prog++;
		if(Maneja_tiempo.month_prog>DIC)
		Maneja_tiempo.month_prog=ENE;
		
		BOUTONS_PILOTES.boton_top_hd=FALSE;
        PILOTE_HORLOGE.month=Maneja_tiempo.month_prog;
			
	}	
	
	if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	{
		Maneja_tiempo.month_prog--;
		if(Maneja_tiempo.month_prog==0x00)
		Maneja_tiempo.month_prog=DIC;
		
		BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		PILOTE_HORLOGE.month=Maneja_tiempo.month_prog;
	}
	
	if(PILOTE_HORLOGE.time_toogle==FALSE)
	{
		PILOTE_HORLOGE.month=0;
		PILOTE_HORLOGE.past_month= PILOTE_HORLOGE.month+2;
	}
	else
	{
		PILOTE_HORLOGE.month=Maneja_tiempo.month_prog;
		PILOTE_HORLOGE.past_month=PILOTE_HORLOGE.month+1;
	}
	break;
	
case PRG_DAY:

	if(BOUTONS_PILOTES.boton_top_hd==TRUE)
	{
		Maneja_tiempo.date_prog++;
		if(Maneja_tiempo.date_prog>31)
		Maneja_tiempo.date_prog=0;
		
		BOUTONS_PILOTES.boton_top_hd=FALSE;
		PILOTE_HORLOGE.date=Maneja_tiempo.date_prog;
	}
	
	if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	{
		Maneja_tiempo.date_prog--;
		if(Maneja_tiempo.date_prog==0xFF)
		Maneja_tiempo.date_prog=31;
		
		BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		PILOTE_HORLOGE.date=Maneja_tiempo.date_prog;
	}
	
	if(PILOTE_HORLOGE.time_toogle==FALSE)
	{
		
		PILOTE_HORLOGE.date=0;	//programar en acomoda_date 0 para apagar		
		PILOTE_HORLOGE.past_date= PILOTE_HORLOGE.date+2;
	}
	else
	{
		PILOTE_HORLOGE.date=Maneja_tiempo.date_prog;
		PILOTE_HORLOGE.past_date=PILOTE_HORLOGE.date+1;
	}
	
	break;
	
	case PRG_YR:
	
	if(BOUTONS_PILOTES.boton_top_hd==TRUE)
	{
		Maneja_tiempo.year_prog++;
		if(Maneja_tiempo.year_prog>59)
		Maneja_tiempo.year_prog=0;
		
		BOUTONS_PILOTES.boton_top_hd=FALSE;
		PILOTE_HORLOGE.year=Maneja_tiempo.year_prog;
		
	}
	
	if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	{
		Maneja_tiempo.year_prog--;
		if(Maneja_tiempo.year_prog==0xFF)
		Maneja_tiempo.year_prog=59;
		
		BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		PILOTE_HORLOGE.year=Maneja_tiempo.year_prog;
		
	}
	
	if(PILOTE_HORLOGE.time_toogle==FALSE)
	{
		
		PILOTE_HORLOGE.year=0;	//programar en acomoda_date 0 para apagar
		PILOTE_HORLOGE.past_year= PILOTE_HORLOGE.year+2;
		
		
	}
	else
	{
		PILOTE_HORLOGE.year=Maneja_tiempo.year_prog;
		PILOTE_HORLOGE.past_year=PILOTE_HORLOGE.year+1;
		
	}
	break;
	

		case PRG_ALRM_SEG:
		if(BOUTONS_PILOTES.boton_top_hd)
	   {
		//****suma 1 segundo   
		
	   PILOTE_HORLOGE.alrm_sec++;
	   if(PILOTE_HORLOGE.alrm_sec>59/*segundos*/)	   
	   PILOTE_HORLOGE.alrm_sec=0;   // si llegó al limite superior de minutos se reinicia a 0 haciendo un bucle
	  //**********************************	  
	   BOUTONS_PILOTES.boton_top_hd=FALSE;
	   PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
	   
	  
	   
	   }	
	  if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	  {
		//****resta 1 segundo   
	   PILOTE_HORLOGE.alrm_sec--;
		  if(PILOTE_HORLOGE.alrm_sec==0xFF)
		  PILOTE_HORLOGE.alrm_sec=59;
		  
		  BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		  PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
		  
		  
	  } 
	   
	   //***********************parpadeo*******************/////////
	   if(PILOTE_HORLOGE.time_toogle==FALSE)
	   {
		   PILOTE_HORLOGE.sec=0;//
		   PILOTE_HORLOGE.past_sec_alrm= PILOTE_HORLOGE.sec+2;
		   //Acomoda_5x32();
		   
	   }
	   else
	   {
		   PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
		   PILOTE_HORLOGE.past_sec_alrm=PILOTE_HORLOGE.sec+1;
		   //Acomoda_5x32();
	   }   
	   	
			  
		break;
		
		case PRG_ALRM_MIN:
		
		if(BOUTONS_PILOTES.boton_top_hd)
	   {
		//****suma 1 segundo   
	   PILOTE_HORLOGE.alrm_min++;
	   if(PILOTE_HORLOGE.alrm_min>59/*segundos*/)	   
	   PILOTE_HORLOGE.alrm_min=0;   // si llegó al limite superior de minutos se reinicia a 0 haciendo un bucle
	  //**********************************	  
	   BOUTONS_PILOTES.boton_top_hd=FALSE;
	   PILOTE_HORLOGE.min=PILOTE_HORLOGE.alrm_min;
	   }	
	  if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	  {
		//****resta 1 segundo   
	   PILOTE_HORLOGE.alrm_min--;
		  if(PILOTE_HORLOGE.alrm_min==0xFF)
		  PILOTE_HORLOGE.alrm_min=59;
		  
		  BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		  PILOTE_HORLOGE.min=PILOTE_HORLOGE.alrm_min;
		  
	  } 
	   
	   //***********************parpadeo*******************/////////
	   if(PILOTE_HORLOGE.time_toogle==FALSE)
	   {
		   PILOTE_HORLOGE.min=0;//
		   PILOTE_HORLOGE.past_min_alrm= PILOTE_HORLOGE.min+2;
		   		   
	   }
	   else
	   {
		   PILOTE_HORLOGE.min=PILOTE_HORLOGE.alrm_min;
		   PILOTE_HORLOGE.past_min_alrm=PILOTE_HORLOGE.alrm_min+1;
	   }   
				
		break;
		
		case PRG_ALRM_HR:
		
		
		if(BOUTONS_PILOTES.boton_top_hd==TRUE)
		{
			PILOTE_HORLOGE.alrm_hr++;
			if(PILOTE_HORLOGE.alrm_hr>23)
			PILOTE_HORLOGE.alrm_hr=0;
			
			BOUTONS_PILOTES.boton_top_hd=FALSE;
			PILOTE_HORLOGE.hour=PILOTE_HORLOGE.alrm_hr;
			
		}
		
		if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
		{
			PILOTE_HORLOGE.alrm_hr--;
			if(PILOTE_HORLOGE.alrm_hr==0xFF)
			PILOTE_HORLOGE.alrm_hr=23;
			
			BOUTONS_PILOTES.boton_dessous_hd=FALSE;
			PILOTE_HORLOGE.hour=PILOTE_HORLOGE.alrm_hr;
			
		}
		
		if(PILOTE_HORLOGE.time_toogle==FALSE)
		{
			if(PILOTE_HORLOGE.alrm_hr!=11)
			PILOTE_HORLOGE.hour=0;
			else
			PILOTE_HORLOGE.hour=0;
			
			PILOTE_HORLOGE.past_hour_alrm= PILOTE_HORLOGE.alrm_hr+2;
		}
		else
		{
			PILOTE_HORLOGE.hour=PILOTE_HORLOGE.alrm_hr;
			PILOTE_HORLOGE.past_hour_alrm=PILOTE_HORLOGE.hour+1;
			//Acomoda_5x32();
		}
		break;

	case PRG_ALRM_ON_OFF:
	
	if(BOUTONS_PILOTES.boton_top_hd==TRUE)
	{
		//significa prendido alarma
		
		On_Off_Options.alarm=TRUE;
		on_audio_alrm(PILOTE_HORLOGE.Alarm_PlayList);
		PILOTE_HORLOGE.alrm_sec=0;
		
		PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
		BOUTONS_PILOTES.boton_top_hd=FALSE;
	}
	
	
	  if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	  {
		  //alarma apagada
	       Execute_audio(SOUND_STOP);
		  PILOTE_HORLOGE.alrm_sec=30;
		  On_Off_Options.alarm=FALSE;
		  PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
		  BOUTONS_PILOTES.boton_dessous_hd=FALSE;
		  
	  }
	
	
	 if(PILOTE_HORLOGE.time_toogle==FALSE)
	 {
		 PILOTE_HORLOGE.sec=0;//
		 PILOTE_HORLOGE.past_sec_alrm= PILOTE_HORLOGE.sec+2;
		 //Acomoda_5x32();
		 
	 }
	 else
	 {
		 PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
		 PILOTE_HORLOGE.past_sec_alrm=PILOTE_HORLOGE.sec+1;
		 //Acomoda_5x32();
	 }
	 
	 break;
	 
	 case PRG_SONIDOS:
			if(BOUTONS_PILOTES.boton_top_hd==TRUE)
			{
				    
					BOUTONS_PILOTES.boton_top_hd=FALSE;
					
					PILOTE_HORLOGE.sound=0; //sonidos prendidos
					PILOTE_HORLOGE.sec=PILOTE_HORLOGE.sound;
					On_Off_Options.sounds=TRUE;
					on_audio(SOUND_FANFARE);
					EEWriteByte(SAVE_SOUND_STATE,PILOTE_HORLOGE.sound);
					
					
			}
			
			if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
			{
					BOUTONS_PILOTES.boton_dessous_hd=FALSE;
					PILOTE_HORLOGE.sound=30; //sonidos apagados
					PILOTE_HORLOGE.sec=PILOTE_HORLOGE.sound;
					Execute_audio(SOUND_STOP);
					EEWriteByte(SAVE_SOUND_STATE,PILOTE_HORLOGE.sound);
					On_Off_Options.sounds=FALSE;
					
					
			}
			
			 if(PILOTE_HORLOGE.time_toogle==FALSE)
			 {
				 PILOTE_HORLOGE.sec=0;//
				 PILOTE_HORLOGE.past_sound= PILOTE_HORLOGE.sec+2;
				 //Acomoda_5x32();
				 
			 }
			 else
			 {
				 PILOTE_HORLOGE.sec=PILOTE_HORLOGE.sound;
				 PILOTE_HORLOGE.past_sound=PILOTE_HORLOGE.sound+1;
				 //Acomoda_5x32();
			 }
			 
			 
	 break;
	 	 
	 case PRG_TIPO_ALARMA:
	 
	 
	 if(BOUTONS_PILOTES.boton_top_hd==TRUE)
	 {
		 	BOUTONS_PILOTES.boton_top_hd=FALSE;
		 	
		 	PILOTE_HORLOGE.knd_alarm++; //sonidos prendidos
			 if(PILOTE_HORLOGE.knd_alarm>2)
			 PILOTE_HORLOGE.knd_alarm=0;
			 
			 PILOTE_HORLOGE.min=PILOTE_HORLOGE.knd_alarm+1;	
			 		 			 		 	
		 	switch (PILOTE_HORLOGE.knd_alarm)
			 {
				 case 0:
					PILOTE_HORLOGE.Alarm_PlayList=SOUND_ALARMA;
				 break;
				 case 1:
				PILOTE_HORLOGE.Alarm_PlayList=SOUND_ALARMA2;
				 break;
				 case 2:
				 PILOTE_HORLOGE.Alarm_PlayList=SOUND_ALARMA3;
				 break;
			 }
			 
			 
		 	Execute_audio(PILOTE_HORLOGE.Alarm_PlayList);
		 	EEWriteByte(SAVE_KIND_ALARM,PILOTE_HORLOGE.knd_alarm);		 
	 }
	 
	 	if(BOUTONS_PILOTES.boton_dessous_hd==TRUE)
	 	{
			 
			 BOUTONS_PILOTES.boton_dessous_hd=FALSE;
			
			 PILOTE_HORLOGE.knd_alarm--; //sonidos prendidos
			 if(PILOTE_HORLOGE.knd_alarm==0xFF)
			 PILOTE_HORLOGE.knd_alarm=2;
			 
			 
			 PILOTE_HORLOGE.min=PILOTE_HORLOGE.knd_alarm+1;			 
			 switch (PILOTE_HORLOGE.knd_alarm)
			 {
				 case 0:
				 PILOTE_HORLOGE.Alarm_PlayList=SOUND_ALARMA;
				 break;
				 case 1:
				 PILOTE_HORLOGE.Alarm_PlayList=SOUND_ALARMA2;
				 break;
				 case 2:
				 PILOTE_HORLOGE.Alarm_PlayList=SOUND_ALARMA3;
				 break;
				 
			 }
			 
			  Execute_audio(PILOTE_HORLOGE.Alarm_PlayList);
			 EEWriteByte(SAVE_KIND_ALARM,PILOTE_HORLOGE.knd_alarm);
			 
		 }
	  if(PILOTE_HORLOGE.time_toogle==FALSE)
	  {
		  PILOTE_HORLOGE.min=0;//
		  PILOTE_HORLOGE.past_knd_alarm =PILOTE_HORLOGE.min+2;
		 
		  
	  }
	  else
	  {
		  PILOTE_HORLOGE.min=PILOTE_HORLOGE.knd_alarm+1;
		  PILOTE_HORLOGE.past_knd_alarm=PILOTE_HORLOGE.knd_alarm+1;
		  
	  }
	 
	 
	 
	 break;
	 
	 
	
}

	
}