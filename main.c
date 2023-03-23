/*
 * Reloj_LED.c
 *
 * Created: 23/07/2018 06:16:35 p.m.
 * Author : Andres
 */ 

#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>
#include "i2c.h"
#include "rtc_ds1307.h"
#include <util/delay.h>	/* Include inbuilt defined Delay header file */
#include "delay.h"
#include <stdbool.h>
#include "interrupts.h"
#include "botones.h"
#include "stdutils.h"
#include "display.h"
#include "atc24.h"
#include "Plays_Externs.h"
#include "WT588D.h"
//uint8_t ejecutaRTC;

/***************Local functions****************/
/**********************************************/
void init_io_ports(void);//this englobes the nexts
/********************************************/ 

void HC595Init(); 
void inicio_timer(void);
void Init_SPI(void);
void Init_Btns(void);
void Init_WT588D_Ports(void);

/*******************************************/
void revisa_acomoda(void);
void revisa_enviar_spi(void);
void revisa_enviar_audio(void);
/***********************************************/


void Init_Btns(void)
{
	
	DDR_BOTONES = 0b00000000;//configura el puerto D como entrada para los botones
	PORT_BOTONES=       0x00;
	
	DDR_BTN5 &=   0b11110111;
	PORT_BTN5&=   0b11110111;
	
	
	/****PORT D ASSIGNED TO BUTTONS*////////
	BOUTONS_PILOTES.boton_num[0]=PORT_IN_BTNS &Mask_BIT0;
	BOUTONS_PILOTES.boton_num[1]=PORT_IN_BTNS &Mask_BIT1;
	BOUTONS_PILOTES.boton_num[2]=PORT_IN_BTNS &Mask_BIT2;
	BOUTONS_PILOTES.boton_num[3]=PORT_IN_BTNS &Mask_BIT3;
	BOUTONS_PILOTES.boton_num[4]=PORT_IN_BTNS &Mask_BIT4;
	/******************************************************////
	BOUTONS_PILOTES.boton_num[5]=PIN_BTN5     &Mask_BIT3;//****PD5 OC1A (PWM) y va al OE del 595 asi que le asignamos PA3 al boton 5
	/********************************************************/////
	BOUTONS_PILOTES.boton_num[6]=PORT_IN_BTNS &Mask_BIT6;
	BOUTONS_PILOTES.boton_num[7]=PORT_IN_BTNS &Mask_BIT7;
}
void HC595Init()
{
	/****Latch**********/////
	HC595_DDR |=  MASK595;
	
	DDR_BARRIDO |= 0b00011111;
	PORT_BARRIDO = 0b00000001;
	
	//HC595_PORT|= (~(1<<HC595_OE_POS));

}
void inicio_timer(void)
{
	cli();
	
	TIMSK = (1<<OCIE0);
	
	TCCR2 = (1 << CS20) |  (1<<CS21) ;// Timer 2 /64
	TCNT2 =0;
	
	
	OCR2 =0x19;//25decimal  // en 16mhz / 64 =.000004 / 250 = .001sec = 1ms   // a 25 100us
	
	
	OCR0=10;
	TCCR0 = (1 << CS02) | (1<< CS00);	
	TCNT0=0;
	
	sei();
	
/***** SET PWM ********************************////////	

    DDRD |=(1<<PD5);

	TCCR1A= (1<<COM1A1) | (1<<COM1A0) | (1<<WGM11) | (1<<WGM10) ;
	TCCR1B= (1<<WGM12)  | (1<<CS10)                             ;
	
	
}
void Init_SPI(void)
{
	
	
	// Set MOSI, SCK as Output
	DDRB|=  (1<<MOSI)|(1<<SCK);	
	SPCR=   (1<<SPE) | (1<<MSTR) | (1<<DORD) | (1<<SPR1) | ((1<<SPR0)); 
	SPSR=   ((1<<SPI2X));
	sei();
	
	
}


void Init_WT588D_Ports(void)
{
	//          rst         busy
	  
	DDRA |= ((1<<PA0) | (0<<PA2));
	//          clk       cs         data
	//          p03	    p02         p01	// del wt588
	DDRC |= (1<<PC6 | (1<<PC5) |(1<<PC4));
	
}

void init_io_ports(void)
{
	HC595Init();
	I2C_Init();	
	Init_Btns();
	inicio_timer();    
	Init_SPI();
	Init_WT588D_Ports();
}

void revisa_enviar_spi(void)
{
	if(PILOTE_SPI.barrer==FALSE)
	{		
		
		send_spi();
		cli();
	
		SPDR=PILOTE_SPI.spi_data[0];
		while(!(SPSR & (1<<SPIF)));
		SPDR=PILOTE_SPI.spi_data[1];
		while(!(SPSR & (1<<SPIF)));
		SPDR=PILOTE_SPI.spi_data[2];
		while(!(SPSR & (1<<SPIF)));
		SPDR=PILOTE_SPI.spi_data[3];
		while(!(SPSR & (1<<SPIF)));
		PILOTE_SPI.barrer=TRUE;		
		
		sei();
	     	
	}
}


void revisa_acomoda(void)
{


switch (MODE_DEPLOYE.selectionner_mode)
	{
case NO_PRG:

	if(PILOTE_HORLOGE.past_sec!=PILOTE_HORLOGE.sec)
		{	

			switch (KIND_DISPLAY.show_date)
			{
				
							
				case CLOCK:
			 	PILOTE_HORLOGE.lee_RTC=TRUE;
				Acomoda_5x32();			
				PILOTE_HORLOGE.past_sec = PILOTE_HORLOGE.sec;	
			//	on_audio(SOUND_RUPEE);
				break;
				
				case CALENDAR:
		       PILOTE_HORLOGE.lee_RTC=TRUE;
			   Acomoda_5X32_DATE();
		       
		       PILOTE_HORLOGE.past_sec = PILOTE_HORLOGE.sec ;
		       break;
			   
			   case ALARM:
			   
			   PILOTE_HORLOGE.lee_RTC=FALSE;
			   
			   PILOTE_HORLOGE.sec=PILOTE_HORLOGE.alrm_sec;
			   PILOTE_HORLOGE.min= PILOTE_HORLOGE.alrm_min;
			   PILOTE_HORLOGE.hour= PILOTE_HORLOGE.alrm_hr;
	         //  PILOTE_HORLOGE.lee_RTC=FALSE;
	           Acomoda_5x32();	
			  // LeeRTC();
	            PILOTE_HORLOGE.past_sec = PILOTE_HORLOGE.sec ;
				break;
			}
		}

	

case PRG_SEG:

	 Mode_de_DEPLOYE();
 
	if(PILOTE_HORLOGE.past_sec!=PILOTE_HORLOGE.sec)
		{ 
	
	
		 Acomoda_5x32();
		 PILOTE_HORLOGE.past_sec=PILOTE_HORLOGE.sec;
		 
		}

	break;
	
	
case PRG_MIN:

	Mode_de_DEPLOYE();

	if(PILOTE_HORLOGE.past_min!=PILOTE_HORLOGE.min)
		{
			
			Acomoda_5x32();
			
			PILOTE_HORLOGE.past_min=PILOTE_HORLOGE.min;
			
	    }

break;

case PRG_HR:

	Mode_de_DEPLOYE();
	if(PILOTE_HORLOGE.past_hour!=PILOTE_HORLOGE.hour)
		{
			
			Acomoda_5x32();
			
			PILOTE_HORLOGE.past_hour=PILOTE_HORLOGE.hour;
		}
break;

case PRG_MTH:



	Mode_de_DEPLOYE();

	if(PILOTE_HORLOGE.past_month!=PILOTE_HORLOGE.month)
		{
			
			Acomoda_5X32_DATE();
			
			PILOTE_HORLOGE.past_month=PILOTE_HORLOGE.month;
            		
		}
break;

case PRG_DAY:

	Mode_de_DEPLOYE();

	if(PILOTE_HORLOGE.past_date!=PILOTE_HORLOGE.date)
{
	
	Acomoda_5X32_DATE();
	
	PILOTE_HORLOGE.past_date=PILOTE_HORLOGE.date;
	
}

break;

case PRG_YR:

	Mode_de_DEPLOYE();

	if(PILOTE_HORLOGE.past_year!=PILOTE_HORLOGE.year)
		{			
			Acomoda_5X32_DATE();			
			PILOTE_HORLOGE.past_year=PILOTE_HORLOGE.year;
        }
break;


case PRG_ALRM_SEG:
   Mode_de_DEPLOYE();
   
   if(PILOTE_HORLOGE.past_sec_alrm!=PILOTE_HORLOGE.sec)
   {
	   
	   Acomoda_5x32();
	   
	   PILOTE_HORLOGE.past_sec_alrm=PILOTE_HORLOGE.sec;
   }   
   
break;

case PRG_ALRM_MIN:
Mode_de_DEPLOYE();

if(PILOTE_HORLOGE.past_min_alrm!=PILOTE_HORLOGE.min)
{
	
	Acomoda_5x32();
	
	PILOTE_HORLOGE.past_min_alrm=PILOTE_HORLOGE.min;
	
}
break;

case PRG_ALRM_HR:

Mode_de_DEPLOYE();
if(PILOTE_HORLOGE.past_hour_alrm!=PILOTE_HORLOGE.hour)
{
	
	Acomoda_5x32();
	
	PILOTE_HORLOGE.past_hour_alrm=PILOTE_HORLOGE.hour;
}
break;

case PRG_ALRM_ON_OFF:

Mode_de_DEPLOYE();
if(PILOTE_HORLOGE.past_sec_alrm!=PILOTE_HORLOGE.sec)
{
	
	Acomoda_5x32();
	
	PILOTE_HORLOGE.past_sec_alrm=PILOTE_HORLOGE.sec;
}
break;


case PRG_SONIDOS:

Mode_de_DEPLOYE();

if(PILOTE_HORLOGE.past_sound!= PILOTE_HORLOGE.sound)
{
	
	Acomoda_5x32();
	
	PILOTE_HORLOGE.past_sound=PILOTE_HORLOGE.sound;
}


break;


case PRG_TIPO_ALARMA:
Mode_de_DEPLOYE();

if(PILOTE_HORLOGE.past_knd_alarm!=PILOTE_HORLOGE.knd_alarm)
{
	Acomoda_5x32();
	PILOTE_HORLOGE.past_knd_alarm=PILOTE_HORLOGE.knd_alarm;
}

break;



	} //enf switch

} //end main


void revisa_despliega(void)
{
	if(PILOTE_SPI.send_store==TRUE)
	{		
		Despliega();
		PILOTE_SPI.send_store=FALSE;
		
	}
	
}



void revisa_juegos(void)
 {
	 
	 
	 cli();
	 PLAYS();
	 sei();
	 
 }


void revisa_enviar_audio(void)
{
	
	if(Drive_WT58.send_audio==TRUE)
	{
			 play_song_secuence();		
	}
	

}

 void revisa_alarmaYsonidos(void)
 {
	if(MODE_DEPLOYE.selectionner_mode==NO_PRG)	
	{	
		if(KIND_DISPLAY.show_date==CLOCK)
		{
		 
		if(PILOTE_HORLOGE.alrm_hr == PILOTE_HORLOGE.hour)
		  {
			if(PILOTE_HORLOGE.alrm_min == PILOTE_HORLOGE.min)
			  {               
		            if(Drive_WT58.alarma==FALSE)
					{		
					
						Drive_WT58.alarma=TRUE; 
						
						on_audio_alrm(PILOTE_HORLOGE.Alarm_PlayList); 
						
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
/*************************************************************************************/
//****************************Prende el reloj si esta apagado***********************//						
			if(ESTADO.ON_OFF==FALSE)
			{
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
						
			}
					
					}
					
					
			}
			else
			{
				if(Drive_WT58.alarma==TRUE)
				{
					Drive_WT58.alarma=FALSE;
				}
			}
	      
		}
		
		if(PILOTE_HORLOGE.min==0)
		{
		  if(Drive_WT58.sonidos_general==FALSE)
		  {
			  Drive_WT58.sonidos_general=TRUE;
			  
			  switch (PILOTE_HORLOGE.hour)
			  {
				  
		/*  Activar para zelda */
		/*		  
			  case 7:
				if(PILOTE_HORLOGE.alrm_hr==7)
					{				
						if (PILOTE_HORLOGE.alrm_min!=0)
							on_audio(SOUND_MORNING);
					
					}
					
					else
					on_audio(SOUND_MORNING);
					
			  break;
			  
			  case 19:
			  if(PILOTE_HORLOGE.alrm_hr==19)
			  {
				if(PILOTE_HORLOGE.alrm_min!=0)
					on_audio(SOUND_NIGHT);
					
			  }
			  else
			  on_audio(SOUND_NIGHT);
			  
			  break;
			 */ 
			  default:			  
			  
			  if((PILOTE_HORLOGE.alrm_hr==PILOTE_HORLOGE.hour)&&(PILOTE_HORLOGE.alrm_min==PILOTE_HORLOGE.min))//	significa que se esta sonando una alarma
				on_audio_alrm(PILOTE_HORLOGE.Alarm_PlayList);
				else
				{				
				
				 if((PORT_IN_BUSY & BUSY_WT588)==FALSE)
				 {
				     
					 on_audio(SOUND_SECRET);	
					 
				 }
				
				
				}
			  break;
			  
			  }
			  
		  }
		  
		}
		
		 else
		 {
			 if(Drive_WT58.sonidos_general==TRUE)
			 {
				 Drive_WT58.sonidos_general=FALSE;
			 }
			 
		 }
		
		}
		
	}
	 
 }
 
int main(void)
{	
	
	init_io_ports();
	HC595Latch();
//  DS1307_setdate(0x00, 0x15, 0X8);
   PILOTE_SPI.recorre_barrido=1;
   
  PILOTE_SPI.  barrer=TRUE;
  PILOTE_SPI. send_store=FALSE;
  PILOTE_SPI. enviar_nuevo=TRUE;
  PILOTE_SPI. next_outbarrido=4;
  
  MODE_DEPLOYE.selectionner_mode=0;
  PILOTE_HORLOGE.time_toogle=TRUE;
  ESTADO.ON_OFF=TRUE;
      
   BOUTONS_PILOTES.briller_change=EEReadByte(SAVE_BRG);   
     DELAY_us(850);
   
   switch (BOUTONS_PILOTES.briller_change)
   {
	   
	   case 0:
	   BOUTONS_PILOTES.briller_change=BRILLO1;
	   EEWriteByte(SAVE_BRG,1);
	   DELAY_us(850);
	   break;
	   case 1:
	   BOUTONS_PILOTES.briller_change=BRILLO1;
	   break;	   
	   case 2:
	   BOUTONS_PILOTES.briller_change=BRILLO2;
	   break;
	   case 3:
	   BOUTONS_PILOTES.briller_change=BRILLO3;
	   break;
	   case 4:
	   BOUTONS_PILOTES.briller_change=BRILLO4;
	   break;
	   
	   default:
	     BOUTONS_PILOTES.briller_change=BRILLO1;
	     EEWriteByte(SAVE_BRG,1);	   
		 DELAY_us(850);  
	     break;
	   
   }
   
   
   if (BOUTONS_PILOTES.briller_change==BRILLO4)
  BOUTONS_PILOTES.boton_briller=BRILLO1;
  else
  BOUTONS_PILOTES.boton_briller=BRILLO4;
  
  
  
  PILOTE_HORLOGE.alrm_sec= EEReadByte(SAVE_ALRM_ON_OFF);
  if(PILOTE_HORLOGE.alrm_sec==0)
  On_Off_Options.alarm=TRUE;
  else
  On_Off_Options.alarm=FALSE;
  
  
  DELAY_us(3000);
  PILOTE_HORLOGE.alrm_min=  EEReadByte(SAVE_ALRM_MIN);
  DELAY_us(3000);
  PILOTE_HORLOGE.alrm_hr= EEReadByte(SAVE_ALRM_HR);
  
   KIND_DISPLAY.show_date=CLOCK;
   PILOTE_HORLOGE.lee_RTC=TRUE;
   LeeRTC();
    // Drive_ornament.how_loops=5;
	 
	 Drive_WT58.rola=0;
	//sound_test();
	
	Drive_WT58.send_audio=FALSE; 
	 Drive_WT58.contador_ms=0;
	 Drive_WT58.protocol_part=0;
	
	 Drive_WT58.suma_ms=TRUE;
	
	PILOTE_HORLOGE.sound = EEReadByte(SAVE_SOUND_STATE);
	 DELAY_us(800);
	PILOTE_HORLOGE.knd_alarm = EEReadByte(SAVE_KIND_ALARM);
	 DELAY_us(800);
//	PILOTE_HORLOGE.volumen =  EEReadByte(SAVE_VOLUMEN);
//	 DELAY_us(800);
	 
	 if(PILOTE_HORLOGE.sound==0)
		On_Off_Options.sounds=TRUE;
		else
		On_Off_Options.sounds=FALSE;
	 
	 Drive_WT58.sonidos_general=FALSE;
	 
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


	 
	 PILOTE_HORLOGE.month= DS1307_get(MONTH);
	 PILOTE_HORLOGE.month= BCDaDecimal(PILOTE_HORLOGE.month);
	 PILOTE_HORLOGE.date = DS1307_get(DATE);//dia numero
	 PILOTE_HORLOGE.date = BCDaDecimal(PILOTE_HORLOGE.date);
	 PILOTE_HORLOGE.year = DS1307_get(YEAR);
	 PILOTE_HORLOGE.year = BCDaDecimal(PILOTE_HORLOGE.year);
	 
	 BOUTONS_PILOTES.boton_top_hd=FALSE;
	 TIMSK|= 0b10000000;
    while (1) 
			{	
				Modulo_Brillo();									
				LeeRTC();							
				
				cli();
				revisa_acomoda();
				sei();								
				
				 revisa_juegos(); 
				
				revisa_despliega();		
				//cli();
				revisa_enviar_spi();			    
		        //sei();			
				
					
				Lee_Botones();	
		//esto evita que al salir del modo ALARMA la hora actual y las variables de desplegado no sean iguales a los de de ALARMA que se estaba leyendo y suene la alarma//**		
				if(PILOTE_HORLOGE.cortar_sonido==TRUE)
				{
					PILOTE_HORLOGE.cortar_sonido=FALSE;
					LeeRTC();
				}
		//*********************************************************************************************************************************************************************		
				
				revisa_enviar_audio();
				revisa_alarmaYsonidos();
				
				
				
				
        
			}//end while
	}//end main