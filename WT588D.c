/*
 * WT588D.c
 *
 * Created: 30/09/2018 11:17:10 p. m.
 *  Author: andre
 */
#include "WT588D.h"
#include "delay.h"


void on_audio(uint8_t rola)
{
	if(On_Off_Options.sounds==TRUE)
	{
	Execute_audio(rola);	
	}
}

void Execute_audio(uint8_t rola)
{
	/*envia audio **********/
	Drive_WT58.on_timer=TRUE;
	Drive_WT58.send_audio=TRUE;
	Drive_WT58.rola=rola;
	Drive_WT58.suma_ms=TRUE;
	TCNT2 = 0;
	/***********************/
}


void on_audio_alrm(uint8_t rola)
{	
		if(On_Off_Options.alarm==TRUE)
		{
			Execute_audio(rola);
	}
	
	
	
}

 
void play_song_secuence(void)
{
	
	
	if(Drive_WT58.on_timer==TRUE)
	{
		Drive_WT58.rota_rola=Drive_WT58.rola;
		//TIMSK|= 0b10000000;
		Drive_WT58.on_timer=FALSE;	
		Drive_WT58.contador_ms=0;
		Drive_WT58.contador_us=0;	
		TCNT2=0;
	}
	
	switch( Drive_WT58.protocol_part)
	{
		
		case 0:
		
		if (Drive_WT58.contador_ms<9)  //   DELAY_ms(100); 7
		{
			
			PORT_DRV_WT588_RST &= (~(RST_WT588)); // (0<<RST_WT588);
			
		}
		else
		{
			PORT_DRV_WT588_RST |= RST_WT588;
			Drive_WT58.protocol_part++;
			Drive_WT58.contador_ms=0;
			Drive_WT58.contador_us=0;
			PORT_DRV_WT588_ALLNO_RST |= CS_WT588;
		}	
		
		break;
		
		case 1:
		
			if (Drive_WT58.contador_ms>20)
			{
				PORT_DRV_WT588_ALLNO_RST &= (~(CS_WT588));
				
			//	PORT_DRV_WT588_ALLNO_RST |= CLOCK_WT588;
				
				Drive_WT58.protocol_part++;
				Drive_WT58.contador_ms=0;
				Drive_WT58.contador_us=0;
				
			}
		
		break;
		
		case 2:
			
		if (Drive_WT58.contador_ms>10)
		{
			Drive_WT58.protocol_part++;
			Drive_WT58.contador_ms=0;
			Drive_WT58.contador_us=0;
			Drive_WT58.time_off_secuence=FALSE;
			//Drive_WT58.i=0;
			PORT_DRV_WT588_ALLNO_RST &= (~( CLOCK_WT588));
		}
		break;
		
		case 3:

//*************************************************************//
/***************************************************************/	
//** saca Datos esto no pude programarlo con interrupciones********///
	for(Drive_WT58.i=0;Drive_WT58.i<8;Drive_WT58.i++)
	{
		PORT_DRV_WT588_ALLNO_RST &= (~( CLOCK_WT588));
		Drive_WT58.comp_rola = Drive_WT58.rota_rola & 0b00000001;
		
		switch (Drive_WT58.comp_rola)
		{
			
			case 0:			
			PORT_DRV_WT588_ALLNO_RST &= (~(DAT_WT588));
			break;
			
			case 1:
			PORT_DRV_WT588_ALLNO_RST |= DAT_WT588;
			break;
		}
		
		Drive_WT58.rota_rola>>=1;
		DELAY_us(15);
		PORT_DRV_WT588_ALLNO_RST |= CLOCK_WT588;
		DELAY_us(22);
		
	}
	PORT_DRV_WT588_ALLNO_RST |= CS_WT588;
	
	Drive_WT58.send_audio=FALSE;
	Drive_WT58.protocol_part=0;
	//TIMSK&= 0b01111111;
	
/****************************************************************/
/******************************************************************/	
	
	
	/*  
		
		//Save this code**************
		********************************
		Drive_WT58.suma_ms=FALSE;
		
			if(Drive_WT58.contador_us>0)
			{
				
			if(Drive_WT58.time_off_secuence==FALSE)
				{	
				
				PORT_DRV_WT588_ALLNO_RST &= (~( CLOCK_WT588));
				Drive_WT58.comp_rola = Drive_WT58.rota_rola & 0b00000001;
				
				switch (Drive_WT58.comp_rola)
				{
					
					case 0:
					
					PORT_DRV_WT588_ALLNO_RST &= (~(DAT_WT588));
					break;
					
					case 1:
					PORT_DRV_WT588_ALLNO_RST |= DAT_WT588;
					break;
					
				}
				Drive_WT58.rota_rola>>=1;				
				Drive_WT58.contador_us=0;
				Drive_WT58.contador_ms=0;
				Drive_WT58.time_off_secuence=TRUE;
			}
			
			else
			{
				PORT_DRV_WT588_ALLNO_RST |= CLOCK_WT588;
				Drive_WT58.i++;
				Drive_WT58.time_off_secuence=FALSE;
				Drive_WT58.contador_us=0;
			}
			
			if(Drive_WT58.i==7)
			{
				Drive_WT58.protocol_part=0;
				Drive_WT58.send_audio=FALSE;
				Drive_WT58.i=0;
				PORT_DRV_WT588_ALLNO_RST |= CS_WT588;
				TIMSK&= 0b01111111;
				
			}
		*//////////////////////////////	****hasta aqui...
	
		break;
	   }
	   
	   
		
	}
	

	
	/////////esto jala es a 3 lineas/////////
/*
Drive_WT58.rota_rola=Drive_WT58.rola;
	PORT_DRV_WT588_RST &= (~(RST_WT588));
	DELAY_ms(5);
	PORT_DRV_WT588_RST |= RST_WT588;
	DELAY_ms(17);
	PORT_DRV_WT588_ALLNO_RST &= (~(CS_WT588));
	DELAY_ms(4);
	*/
/*
	for(Drive_WT58.i=0;Drive_WT58.i<8;Drive_WT58.i++)
	 {
		PORT_DRV_WT588_ALLNO_RST &= (~( CLOCK_WT588));
		Drive_WT58.comp_rola = Drive_WT58.rota_rola & 0b00000001;
	
		switch (Drive_WT58.comp_rola)
		{
		
		case 0:
		
		PORT_DRV_WT588_ALLNO_RST &= (~(DAT_WT588));
		break;
		
		case 1:
		PORT_DRV_WT588_ALLNO_RST |= DAT_WT588;
		break;		
		}
		
		Drive_WT58.rota_rola>>=1;
		DELAY_us(30);
		PORT_DRV_WT588_ALLNO_RST |= CLOCK_WT588;
		DELAY_us(30);
		
	 }
        PORT_DRV_WT588_ALLNO_RST |= CS_WT588;
		
		Drive_WT58.send_audio=FALSE;

	*/	
		

/*
void compare_rola(void)
{
	if(Drive_WT58.rota_rola & 1)
	{
		
	}
}
*/

/*
void Sequence_Send_Audio(void)
{
	
	if(Drive_WT58.on_timer==TRUE)
	 {	 
		Drive_WT58.rota_rola=Drive_WT58.rola; 
	 TIMSK|= 0b10000000;
	 Drive_WT58.on_timer=FALSE;
	 PORT_DRV_WT588C |= 0b01000000;//dat=1;
	 TCNT2=0;
	 }
	 	 
switch( Drive_WT58.protocol_part) 

	 	 
	{ 
		
	case 0:
		
	 if (Drive_WT58.contador_ms<50)  //   DELAY_ms(100); 7
	 { 	 
		 
		PORT_DRV_WT588A &=  0b11111110;  // (0<<RST_WT588);     
	 
	 }
	 else
	 {
		  PORT_DRV_WT588A |= 0b00000001;//(1<<RST_WT588);
		  Drive_WT58.protocol_part++;	
		  Drive_WT58.contador_ms=0;	  
		  PORT_DRV_WT588C |= 0b01000000;//(1	<<DAT_WT588);
	  }
	 
	 
	
	break;
	
	case 1:	 
		 
		 if(Drive_WT58.contador_ms>17)
		 {		 
		 Drive_WT58.protocol_part++;
		  
		 Drive_WT58.contador_ms=0;
		 PORT_DRV_WT588C &= 0b10111111; //(0<<DAT_WT588);
		 }
		
	break;
	
	case 2:	
	
	 if(Drive_WT58.contador_ms>5)
	 {
		 Drive_WT58.contador_ms=0;
		 PORT_DRV_WT588C |= 0b01000000;//DAT=1;
		// OCR2 = 75;
		 // TCNT2=0;
		Drive_WT58.protocol_part++; 
	 }
	break;
	
	case 3:	 
	
		 for(Drive_WT58.i=0;Drive_WT58.i<8;Drive_WT58.i++)
		 {
			 PORT_DRV_WT588C |=  0b01000000;      // (1<<DAT_WT588);
			 if(Drive_WT58.rota_rola & 1)
			 {
				 DELAY_us(600);      // 400us /
				 PORT_DRV_WT588C &= 0b10111111; //(0<<DAT_WT588);
				 DELAY_us(300);
			 }
			 else 
			 {
				 DELAY_us(300); 	   // 200us
				 PORT_DRV_WT588C &= 0b10111111;     // (0<<DAT_WT588);
				 DELAY_us(600);       // 400us
			 }
			 
			 Drive_WT58.rota_rola = Drive_WT58.rota_rola>>1;
			// PORT_DRV_WT588C |=  0b01000000;      // (1<<DAT_WT588);
		 }
		 
		 Drive_WT58.send_audio=FALSE;
		// Drive_WT58.on_timer=FALSE;
		 TIMSK&= 0b01111111;
		 Drive_WT58.contador_ms=0;
		 Drive_WT58.protocol_part=0;
		 
	//	 sei();
		 break;
		
		
			 PORT_DRV_WT588C |=  0b01000000;      // (1<<DAT_WT588);
			 if(Drive_WT58.rota_rola & 1)
			 {
				 DELAY_us(400);      // 400us /
				 PORT_DRV_WT588C &= 0b10111111; //(0<<DAT_WT588);
				 DELAY_us(200);
			 }
			 else {
				 DELAY_us(200); 	   // 200us
				 PORT_DRV_WT588C &= 0b10111111;     // (0<<DAT_WT588);
				 DELAY_us(400);       // 400us
			 }
			 
			 Drive_WT58.rota_rola = Drive_WT58.rota_rola>>1;
			 PORT_DRV_WT588C |=  0b01000000;      // (1<<DAT_WT588);
			
		
		
		Drive_WT58.send_audio=FALSE;
		Drive_WT58.on_timer=FALSE;
		 TIMSK&= 0b01111111;
		 Drive_WT58.contador_ms=0;
		 Drive_WT58.protocol_part=0;
	break;
	
	
		 }
		 
	*/	 
	 
	 
	 
	
	
