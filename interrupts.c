/*
 * interrupts.c
 *
 * Created: 23/07/2018 09:57:34 p.m.
 *  Author: Andres
 */ 
#include "interrupts.h"
#include "stdutils.h"
#include "delay.h"
#include <util\delay.h>
#include "botones.h"
#include "display.h"
#include "Plays_Externs.h"
#include "WT588D.h"


ISR(TIMER0_COMP_vect)
	{		
		cli();		
			PILOTE_HORLOGE.take_time1++;
			if(PILOTE_HORLOGE.take_time1>100)
			{
				
				
				PILOTE_HORLOGE.take_time1=0;
				switch (PILOTE_HORLOGE.time_toogle)
				{
					case TRUE:
					
					PILOTE_HORLOGE.time_toogle=FALSE;
					if(MODE_DEPLOYE.selectionner_mode>NO_PRG)
					PILOTE_SPI.checa_parpadea_12AM=TRUE;
					
					break;
					
					case FALSE:
					PILOTE_HORLOGE.time_toogle=TRUE;
					if(MODE_DEPLOYE.selectionner_mode>NO_PRG)
					PILOTE_SPI.checa_parpadea_12AM=FALSE;
					break;
				}
			}
			
			PILOTE_SPI.barrer=FALSE;   
			
			
			 // toggles the led
		
			
		PILOTE_HORLOGE.take_time2_Triforce++;
		if(PILOTE_HORLOGE.take_time2_Triforce>259)
		{		
		PILOTE_HORLOGE.take_time2_Triforce=0;
		
		Drive_ornament.execute_mov++;		
		}
		
			
			
			//   enviar_nuevo=TRUE;
	//	}//end if
	
	
	if (KIND_DISPLAY.show_date!=CLOCK)
	{
		KIND_DISPLAY.show_count++;
		
		
			
			if(KIND_DISPLAY.show_date==CALENDAR)
			{
				
				if(KIND_DISPLAY.show_count>33000)
				{				
					
					KIND_DISPLAY.show_date=CLOCK;
					KIND_DISPLAY.show_count=0;
				}
		
			}
		
		
			
			if(KIND_DISPLAY.show_date==ALARM)
			{
				
				if(KIND_DISPLAY.show_count>4500)
				{				
				KIND_DISPLAY.show_date=CLOCK;
				PILOTE_HORLOGE.lee_RTC=TRUE;
				KIND_DISPLAY.show_count=0;
				PILOTE_HORLOGE.cortar_sonido=TRUE;				
				}
			}
	}
	
	TCNT0 = 0;   // reset counter
	sei();
	
	
	}

		
ISR(TIMER2_COMP_vect)
{	
	
	
// cada vuelta es de 100uf
cli();
 if(Drive_WT58.suma_ms==TRUE)	
 {
	if(Drive_WT58.contador_us>10)
	{
		Drive_WT58.contador_ms++;
		Drive_WT58.contador_us=0;
	}
 }

	
	Drive_WT58.contador_us++;

/*	
if (MODE_DEPLOYE.selectionner_mode==NO_PRG)
	{
	
	Drive_ornament.tiempo_entre_brillos++;
	
	if(Drive_ornament.tiempo_entre_brillos>13000)
	{
		Drive_ornament.contador_vueltas++;
		if(Drive_ornament.contador_vueltas>3)
		Drive_ornament.contador_vueltas=0;
		Drive_ornament.tiempo_entre_brillos=0;
	}
	
	
 switch (Drive_ornament.contador_vueltas)
 {

 case 0: 	
	if (Drive_ornament.contador_us<3)
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		PILOTE_SPI.OUT_BARRIDO[4]|= 0xFFFF;
	}
	else
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		PILOTE_SPI.OUT_BARRIDO[4]|= 0xFFFF;
		if(Drive_ornament.contador_us==4)
		{
			Drive_ornament.contador_us=0;
		}
		
	}
break;

case 1:

if (Drive_ornament.contador_us<3)
{
	PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
	PILOTE_SPI.OUT_BARRIDO[4]|= 0xFFFF;
}
else
{
	PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
	//PILOTE_SPI.OUT_BARRIDO[4]|= 0x0000;
	if(Drive_ornament.contador_us==4)
	{
		Drive_ornament.contador_us=0;
	}
	
}
	
	
	break;
	
	case 2:
	
	
	if (Drive_ornament.contador_us<2)
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		PILOTE_SPI.OUT_BARRIDO[4]|= 0xFFFF;
	}
	else
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		//	PILOTE_SPI.OUT_BARRIDO[4]|= 0x0000;
		if(Drive_ornament.contador_us==3)
		{
			Drive_ornament.contador_us=0;
		}
		
	}
	
	break;
	
	case 3:
	if (Drive_ornament.contador_us<3)
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		PILOTE_SPI.OUT_BARRIDO[4]|= 0xFFFF;
	}
	else
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		//PILOTE_SPI.OUT_BARRIDO[4]|= 0x0000;
		if(Drive_ornament.contador_us==4)
		{
			Drive_ornament.contador_us=0;
		}
		
	}
	
	break;
	
        }
}//end if selectioner mode
	else
	{
		PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
		
	}
	
Drive_ornament.contador_us++;


	
	sei();
*/	
	
	TCNT2=0;
	
	
		
	
	
}
	

void Modulo_Brillo(void)
{
if(ESTADO.ON_OFF==TRUE)  
{
  if(BOUTONS_PILOTES.boton_briller!=BOUTONS_PILOTES.briller_change)
  {
	  if(BOUTONS_PILOTES.briller_change>BOUTONS_PILOTES.boton_briller)
	  {
		  BOUTONS_PILOTES.boton_briller++;
	      OCR1A=BOUTONS_PILOTES.boton_briller;
	  }
	  else
	  {
		  if(BOUTONS_PILOTES.briller_change<BOUTONS_PILOTES.boton_briller)
		  {
		  BOUTONS_PILOTES.boton_briller--;
		  OCR1A=BOUTONS_PILOTES.boton_briller;
		  }
	  }
	  
  }// endif bouton_pilotes
}//end if estado on off

  
  else
  	PORTD|= (1<<PD5);
	
	
	
}



void HC595Latch(void)
{
	
	//Pulse the Store Clock
	HC595_PORT|=(1<<HC595_ST_CP_POS);//HIGH
	_delay_loop_1(1);

	HC595_PORT&=(~(1<<HC595_ST_CP_POS));//LOW
	_delay_loop_1(1);

}

uint8_t DecimalToBCD (uint8_t decimalByte)
{
	return (((decimalByte / 10) << 4) | (decimalByte % 10));
}

unsigned char BCDaDecimal(unsigned char bcdByte)
{
	return (((bcdByte & 0xF0) >> 4)*10) + (bcdByte & 0x0F);
}


void LeeRTC(void)
{
  
  if(MODE_DEPLOYE.selectionner_mode==NO_PRG)
{
  if(PILOTE_HORLOGE.lee_RTC==TRUE)	
  	{
		  
	PILOTE_HORLOGE.sec  = DS1307_get(SEC);
	PILOTE_HORLOGE.sec  = BCDaDecimal(PILOTE_HORLOGE.sec);
	
	PILOTE_HORLOGE.min  = DS1307_get(MIN);
	PILOTE_HORLOGE.min  = BCDaDecimal(PILOTE_HORLOGE.min);
	PILOTE_HORLOGE.hour = DS1307_get(HOUR);
	PILOTE_HORLOGE.hour = BCDaDecimal(PILOTE_HORLOGE.hour);
	
	
	if((KIND_DISPLAY.show_date==CALENDAR )|| (MODE_DEPLOYE.selectionner_mode==PRG_MTH) || (MODE_DEPLOYE.selectionner_mode==PRG_DAY) || (MODE_DEPLOYE.selectionner_mode==PRG_YR) )
	  {	  
	  
	PILOTE_HORLOGE.month= DS1307_get(MONTH);
	PILOTE_HORLOGE.month= BCDaDecimal(PILOTE_HORLOGE.month);
	PILOTE_HORLOGE.date = DS1307_get(DATE);//dia numero
    PILOTE_HORLOGE.date = BCDaDecimal(PILOTE_HORLOGE.date);
	PILOTE_HORLOGE.year = DS1307_get(YEAR);
	PILOTE_HORLOGE.year = BCDaDecimal(PILOTE_HORLOGE.year);
	
	  }
	
	
   }
	  
	
}
}


void Acomoda_5x32(void)
{
uint32_t aux_rev_sec; 
	/******************************************************************************************/
	/* Aqui se Acomoda OUT_BARRIDO(0);                                                       */

	PILOTE_SPI.temp_32_SH = PILOTE_HORLOGE.hour;
	if(PILOTE_SPI.temp_32_SH!=0){
		
		if(PILOTE_SPI.temp_32_SH<12){
			//temp_32_SH= NUM_SALIDAS-temp_32_SH;// en temp32 cantidad de ceros


		//	if(PILOTE_SPI.OUT_BARRIDO[0]!= CLR_UP)
			PILOTE_SPI.OUT_BARRIDO[0]=CLR_UP; //pone en ff
			
			PILOTE_SPI.tmp_acmd=24-PILOTE_SPI.temp_32_SH;
			PILOTE_SPI.OUT_BARRIDO[0]= PILOTE_SPI.OUT_BARRIDO[0]>>(PILOTE_SPI.tmp_acmd-1);
			PILOTE_SPI.OUT_BARRIDO[0]&=   0XFFFFFE00;
		}
		else
		{
			if(PILOTE_SPI.temp_32_SH != 12)
			{
			//	if(PILOTE_SPI.OUT_BARRIDO[0]!= CLR_UP)
				PILOTE_SPI.OUT_BARRIDO[0]=CLR_UP; //pone en ff				
				PILOTE_SPI.OUT_BARRIDO[0]= PILOTE_SPI.OUT_BARRIDO[0]>>(32-(PILOTE_SPI.temp_32_SH+9));// 8 de los minutos +1 de desfase				
				PILOTE_SPI.OUT_BARRIDO[0] &= 0xFFE00000;
			}
			else//if(temp_32_SH=12)
			{
				PILOTE_SPI.OUT_BARRIDO[0]=0;				
				PILOTE_SPI.OUT_BARRIDO[0]|= 0x100000; //posicion de 12 PM
			}			
		}				
	}
	else {		
		if(PILOTE_SPI.temp_32_SH==0)
		{
			
          if(MODE_DEPLOYE.selectionner_mode==NO_PRG)
		  {
			PILOTE_SPI.OUT_BARRIDO[0]=0;
			PILOTE_SPI.OUT_BARRIDO[0]|= 0x100;//	Posicion de 12AM
		  }
		  else
		  {
			  
			  if((MODE_DEPLOYE.selectionner_mode==PRG_HR) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_HR)||(MODE_DEPLOYE.selectionner_mode==PRG_VOLUMEN))
			  {
			    if(PILOTE_SPI.checa_parpadea_12AM)
				{				
				
						PILOTE_SPI.OUT_BARRIDO[0]=0;  
				}
				else
				{
					PILOTE_SPI.OUT_BARRIDO[0]=0;
					PILOTE_SPI.OUT_BARRIDO[0]|= 0x100;
				}			
			
			  }
			  else// if mode_deploye <> prg any hour
			  {
				  PILOTE_SPI.OUT_BARRIDO[0]=0;
				  PILOTE_SPI.OUT_BARRIDO[0]|= 0x100;
			  }
			  
		  }
		}
	}
	
	//***********minutos
	PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.min;
	PILOTE_SPI.temp_32_SH=PILOTE_HORLOGE.min;
	if(PILOTE_SPI.tmp_acmd==CERO)
	{
		PILOTE_SPI.temp_32_SH  =  1;
		PILOTE_SPI.tmp_acmd= 1;
		
	}

	if(PILOTE_SPI.tmp_acmd>=MOD_S1){
		PILOTE_SPI.tmp_acmd-= (MOD_S1-1);
		
		//if(PILOTE_SPI.temp_32_SH!= CLR_UP)
		PILOTE_SPI.temp_32_SH = CLR_UP;
		
		PILOTE_SPI.tmp_acmd= NUM_SALIDAS-PILOTE_SPI.tmp_acmd;
		PILOTE_SPI.temp_32_SH= PILOTE_SPI.temp_32_SH>>(PILOTE_SPI.tmp_acmd);
		PILOTE_SPI.OUT_BARRIDO[0]|= PILOTE_SPI.temp_32_SH;        ///////////////////////////////REV//////////////////		
	}	
	/********************************************************************/
	/*      OUT_BARRIDO(1);                                            */
	if(PILOTE_HORLOGE.min==0)
	{
		PILOTE_SPI.tmp_acmd = NUM_MIN;
	}
	else
	{
		PILOTE_SPI.tmp_acmd = PILOTE_HORLOGE.min;

	}
	//******salida  1=51 segundo   32 = 19      ******************//
	if(PILOTE_SPI.tmp_acmd >= 20)
	{
		PILOTE_SPI.tmp_acmd = (PILOTE_SPI.tmp_acmd-19);

		//if(PILOTE_SPI.OUT_BARRIDO[1]!=CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[1]=CLR_UP;

		if(PILOTE_SPI.tmp_acmd==0x29)  ///MIN = 60
		{
			PILOTE_SPI.OUT_BARRIDO[1]&= 0;
		}
		else{
			if(PILOTE_SPI.tmp_acmd>32)
			PILOTE_SPI.tmp_acmd=32;
			
			PILOTE_SPI.OUT_BARRIDO[1]= PILOTE_SPI.OUT_BARRIDO[1]>>(32-PILOTE_SPI.tmp_acmd);
		}

	}
	else
	{
		if(PILOTE_SPI.OUT_BARRIDO[1]!=0)
		PILOTE_SPI.OUT_BARRIDO[1]=0;
	}
	/******************************************************************************/
	/**   OUTBARRIDO[2]                                            ************/
	PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.min;

	if(PILOTE_SPI.tmp_acmd==0)
	 PILOTE_SPI.tmp_acmd=NUM_MIN;
	
	if(PILOTE_SPI.tmp_acmd<=18)
	{
		//if(PILOTE_SPI.OUT_BARRIDO[2]!=CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[2]= CLR_UP;
		
		PILOTE_SPI.tmp_acmd = 19-PILOTE_SPI.tmp_acmd;
		PILOTE_SPI.OUT_BARRIDO[2] = PILOTE_SPI.OUT_BARRIDO[2]>>PILOTE_SPI.tmp_acmd;
		PILOTE_SPI.OUT_BARRIDO[2]&=  0xFFFFE000;
	}
	else
	{
		
		if(PILOTE_SPI.tmp_acmd==60)
		{
			if((MODE_DEPLOYE.selectionner_mode==PRG_MIN)||(MODE_DEPLOYE.selectionner_mode==PRG_ALRM_MIN)||(MODE_DEPLOYE.selectionner_mode== PRG_TIPO_ALARMA))
			{
		
		  PILOTE_SPI.OUT_BARRIDO[2] = PILOTE_SPI.checa_parpadea_12AM ? 0 : 0x1000;
				
			}
			else
			{
				PILOTE_SPI.OUT_BARRIDO[2]=CLR_UP;
				PILOTE_SPI.OUT_BARRIDO[2] &=  0x1000;
			}
		}
		else
		PILOTE_SPI.OUT_BARRIDO[2]=0xFFFFE000;
	}
	
	/*******segundos***********************/////
	PILOTE_SPI.tmp_acmd =  PILOTE_HORLOGE.sec;
if(PILOTE_SPI.tmp_acmd==0)
{	
	if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF) || (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
	{
		if(PILOTE_SPI.checa_parpadea_12AM)
		{
			PILOTE_SPI.tmp_acmd=0;
		}	
	else      // if(PILOTE_SPI.tmp_acmd==0)
	
	PILOTE_SPI.tmp_acmd=60;
	
	}
	else
	PILOTE_SPI.tmp_acmd=60;
}
	
	if(PILOTE_SPI.tmp_acmd>47)
	{
		PILOTE_SPI.tmp_acmd=PILOTE_SPI.tmp_acmd-47;
		//if(PILOTE_SPI.temp_32_SH!=CLR_UP)
		PILOTE_SPI.temp_32_SH=CLR_UP;
		
		if(PILOTE_SPI.tmp_acmd==13){// es igual a 60
			 PILOTE_SPI.OUT_BARRIDO[2]|=0xFFF;
	}
		else// es igual a 60
		{
			PILOTE_SPI.temp_32_SH= PILOTE_SPI.temp_32_SH>>(32-PILOTE_SPI.tmp_acmd);
			//PILOTE_SPI.OUT_BARRIDO[2]=0;
			PILOTE_SPI.OUT_BARRIDO[2]|=PILOTE_SPI.temp_32_SH;
			
			if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
			{
				aux_rev_sec = PILOTE_SPI.checa_parpadea_12AM ? 0xFFFFE000 :  0X1FFF;
				
				if(aux_rev_sec==0xFFFFE000)
				{
					PILOTE_SPI.OUT_BARRIDO[2] &= aux_rev_sec;
				}
				else
				{
			//		if(PILOTE_SPI.temp_32_SH!=CLR_UP)
					PILOTE_SPI.temp_32_SH=CLR_UP;
					
					PILOTE_SPI.temp_32_SH= PILOTE_SPI.temp_32_SH>>(32-PILOTE_SPI.tmp_acmd);
					PILOTE_SPI.OUT_BARRIDO[2] |= PILOTE_SPI.temp_32_SH;
				}				
				
			}
			
		}
	}
	/******************************************************************************/
	/**   OUTBARRIDO[3]                                                ************/

	if(PILOTE_HORLOGE.sec==0)
	{
		if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
		{		
			if(PILOTE_SPI.checa_parpadea_12AM)			
			{
				PILOTE_SPI.tmp_acmd=0;
			}
			else
			 PILOTE_SPI.tmp_acmd = NUM_MIN-1;
					
	    }
		else
		PILOTE_SPI.tmp_acmd = NUM_MIN-1;
	}
	else
	{
		PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.sec;
	}

	if(PILOTE_SPI.tmp_acmd>15)
	{

		PILOTE_SPI.tmp_acmd=PILOTE_SPI.tmp_acmd-15;
		//if(PILOTE_SPI.OUT_BARRIDO[3]!= CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[3]=  CLR_UP;
		
		if(PILOTE_SPI.tmp_acmd>32)
		PILOTE_SPI.tmp_acmd=32;		
		
		PILOTE_SPI.OUT_BARRIDO[3] = PILOTE_SPI.OUT_BARRIDO[3]>>(32-PILOTE_SPI.tmp_acmd);
		
		if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
		{
			aux_rev_sec = PILOTE_SPI.checa_parpadea_12AM ? 0 :PILOTE_SPI.OUT_BARRIDO[3];
			PILOTE_SPI.OUT_BARRIDO[3] |= aux_rev_sec;
		}
		
	}
	else
	{
		if(PILOTE_SPI.OUT_BARRIDO[3]!=0)
		PILOTE_SPI.OUT_BARRIDO[3]=0;
		
		if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) ||(MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
		{
			aux_rev_sec = PILOTE_SPI.checa_parpadea_12AM ? 0 :PILOTE_SPI.OUT_BARRIDO[3];
			PILOTE_SPI.OUT_BARRIDO[3] |= aux_rev_sec;			
		}		
	}
	/******************************************************************************/
	/**   OUTBARRIDO[4]                                                ************/
	
	PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.sec;
			 
	if(PILOTE_HORLOGE.sec==0x00)
	{
		PILOTE_SPI.tmp_acmd=60;
	}

	if(PILOTE_SPI.tmp_acmd<=15)
	{
		
		//tmp_acmd= 32-tmp_acmd;
		
		//if(PILOTE_SPI.OUT_BARRIDO[4]!=CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[4]=CLR_UP;              //      1111 1111 1000 0000 0000 0000 0000 0000
		                                               //      0000 0000 0000 0000 0000 0000 0000 0000
		PILOTE_SPI.OUT_BARRIDO[4]=PILOTE_SPI.OUT_BARRIDO[4]>>(16-PILOTE_SPI.tmp_acmd);
		PILOTE_SPI.OUT_BARRIDO[4]=PILOTE_SPI.OUT_BARRIDO[4]<<(1);
		PILOTE_SPI.OUT_BARRIDO[4]&=  0xFFFE0000;		
		
		if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
		{
			aux_rev_sec= PILOTE_SPI.checa_parpadea_12AM ? 0 : 0xFFFE0000;
			PILOTE_SPI.OUT_BARRIDO[4] &= aux_rev_sec; 
      	}       
	
	}
	else
	{
		if(PILOTE_SPI.tmp_acmd!=60)
		{
			PILOTE_SPI.OUT_BARRIDO[4]|= 0XFFFE0000;
			
			if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
			{
				
				PILOTE_SPI.OUT_BARRIDO[4] |= PILOTE_SPI.checa_parpadea_12AM ? 0 : 0xFFFE0000;				
				
			}
			
		}
		else
		{
			PILOTE_SPI.OUT_BARRIDO[4]= 0xFFFF0000;
			if((MODE_DEPLOYE.selectionner_mode==PRG_SEG) || (MODE_DEPLOYE.selectionner_mode==PRG_ALRM_ON_OFF)|| (MODE_DEPLOYE.selectionner_mode==PRG_SONIDOS))
			{
				
				PILOTE_SPI.OUT_BARRIDO[4] = PILOTE_SPI.checa_parpadea_12AM ? 0 : 0xFFFF0000;
			
			
		     }
		
       }


	}
	
	
}



void Acomoda_5X32_DATE(void)
{
uint32_t	aux_rev_sec;
	//*******OUT_BARRIDO[0]**************///////////
	
	switch(PILOTE_HORLOGE.month)
	{
		case 0:
		//if(PILOTE_SPI.OUT_BARRIDO[0]!=0)
		PILOTE_SPI.OUT_BARRIDO[0]=0x0;
		
		break;
		
		case ENE:       
		
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000000001000000000001000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000000001000000000001000000000;
		break;
		
		case FEB:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000000010000000000010000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000000010000000000010000000000;
		
		break;
		
		case MAR:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000000100000000000100000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000000100000000000100000000000;
		
		break;
		
		
		case ABR:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000001000000000001000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000001000000000001000000000000;
		
		break;
		
		case MAY2:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000010000000000010000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000010000000000010000000000000;
		
		break;
		
		case JUN:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000100000000000100000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000100000000000100000000000000;
		
		break;
		
		case JUL:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00001000000000001000000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00001000000000001000000000000000;
		
		break;
		
		case AGO2:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00010000000000010000000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00010000000000010000000000000000;
		
		break;
		
		case SEP2:
		
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00100000000000100000000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00100000000000100000000000000000;
		
		break;
		
		case OCT:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b01000000000001000000000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b01000000000001000000000000000000;
		
		break;
		
		case NOV:
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b10000000000010000000000000000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b10000000000010000000000000000000;
		
		break;
		
		case DIC:
		
		if(PILOTE_SPI.OUT_BARRIDO[0]!=0b00000000000100000000000100000000)
		PILOTE_SPI.OUT_BARRIDO[0]=0b00000000000100000000000100000000;
		
		break;
	}
	PILOTE_SPI.OUT_BARRIDO[0]&=0xFFFFFF00;
	
	/************OUT_BARRIDO[1]********************////////////////////
	
	if(PILOTE_HORLOGE.date==0)
	{
		PILOTE_SPI.tmp_acmd = 0;
	}
	else
	{
		PILOTE_SPI.tmp_acmd = PILOTE_HORLOGE.date;

	}
	//******salida  1=51 segundo   32 = 19      ******************//
	if(PILOTE_SPI.tmp_acmd > 19)
	{
		PILOTE_SPI.tmp_acmd = (PILOTE_SPI.tmp_acmd-19);

		//if(PILOTE_SPI.OUT_BARRIDO[1]!=CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[1]=CLR_UP;

		if(PILOTE_SPI.tmp_acmd==0x29)  ///MIN = 60
		{
			PILOTE_SPI.OUT_BARRIDO[1]&= 0;
		}
		else{
			if(PILOTE_SPI.tmp_acmd>32)
			PILOTE_SPI.tmp_acmd=32;
			
			PILOTE_SPI.OUT_BARRIDO[1]= PILOTE_SPI.OUT_BARRIDO[1]>>(32-PILOTE_SPI.tmp_acmd);
		}

	}
	else
	{
		if(PILOTE_SPI.OUT_BARRIDO[1]!=0)
		PILOTE_SPI.OUT_BARRIDO[1]=0;
	}
		
	
	/*****OUT_BARRIDO[2]*///////////
	
	PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.date;

	if(PILOTE_SPI.tmp_acmd<19)
	{
	//	if(PILOTE_SPI.OUT_BARRIDO[2]!=CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[2]= CLR_UP;
	
	if(PILOTE_SPI.tmp_acmd==0)
	{
		PILOTE_SPI.OUT_BARRIDO[2]=0;
	}
		else
		{	
		
		PILOTE_SPI.tmp_acmd = 19-PILOTE_SPI.tmp_acmd;
		PILOTE_SPI.OUT_BARRIDO[2] = PILOTE_SPI.OUT_BARRIDO[2]>>PILOTE_SPI.tmp_acmd;
		PILOTE_SPI.OUT_BARRIDO[2]&=  0xFFFFE000;
		}
	}

	else
	{		
		
		PILOTE_SPI.OUT_BARRIDO[2]=0xFFFFE000;
		
	}	
	
	/*************************acomoda año*////////////////////
	
	PILOTE_SPI.tmp_acmd =  PILOTE_HORLOGE.year;
	if(PILOTE_SPI.tmp_acmd==0)
	{
		if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
		{
			if(PILOTE_SPI.checa_parpadea_12AM)
			{
				PILOTE_SPI.tmp_acmd=0;
			}
			else      // if(PILOTE_SPI.tmp_acmd==0)
			
			PILOTE_SPI.tmp_acmd=60;
			
		}
		else
		PILOTE_SPI.tmp_acmd=60;
	}
	
	if(PILOTE_SPI.tmp_acmd>47)
	{
		PILOTE_SPI.tmp_acmd=PILOTE_SPI.tmp_acmd-47;
		//if(PILOTE_SPI.temp_32_SH!=CLR_UP)
		PILOTE_SPI.temp_32_SH=CLR_UP;
		
		if(PILOTE_SPI.tmp_acmd==13){// es igual a 60
			PILOTE_SPI.OUT_BARRIDO[2]|=0xFFF;
		}
		else// es igual a 60
		{
			PILOTE_SPI.temp_32_SH= PILOTE_SPI.temp_32_SH>>(32-PILOTE_SPI.tmp_acmd);
			//PILOTE_SPI.OUT_BARRIDO[2]=0;
			PILOTE_SPI.OUT_BARRIDO[2]|=PILOTE_SPI.temp_32_SH;
			
			if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
			{
				aux_rev_sec = PILOTE_SPI.checa_parpadea_12AM ? 0xFFFFE000 :  0X1FFF;
				
				if(aux_rev_sec==0xFFFFE000)
				{
					PILOTE_SPI.OUT_BARRIDO[2] &= aux_rev_sec;
				}
				else
				{
			//		if(PILOTE_SPI.temp_32_SH!=CLR_UP)
					PILOTE_SPI.temp_32_SH=CLR_UP;
					
					PILOTE_SPI.temp_32_SH= PILOTE_SPI.temp_32_SH>>(32-PILOTE_SPI.tmp_acmd);
					PILOTE_SPI.OUT_BARRIDO[2] |= PILOTE_SPI.temp_32_SH;
				}				
			}			
		}		
	}
	/******************************************************************************/
	/**   OUTBARRIDO[3]                                                ************/

	if(PILOTE_HORLOGE.year==0)
	{
		if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
		{
			if(PILOTE_SPI.checa_parpadea_12AM)
			{
				PILOTE_SPI.tmp_acmd=0;
			}
			else
			PILOTE_SPI.tmp_acmd = NUM_MIN-1;
			
		}
		else
		PILOTE_SPI.tmp_acmd = NUM_MIN-1;
	}
	else
	{
		PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.year;
	}

	if(PILOTE_SPI.tmp_acmd>15)
	{

		PILOTE_SPI.tmp_acmd=PILOTE_SPI.tmp_acmd-15;
		//if(PILOTE_SPI.OUT_BARRIDO[3]!= CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[3]=  CLR_UP;
		
		if(PILOTE_SPI.tmp_acmd>32)
		PILOTE_SPI.tmp_acmd=32;
		PILOTE_SPI.OUT_BARRIDO[3] = PILOTE_SPI.OUT_BARRIDO[3]>>(32-PILOTE_SPI.tmp_acmd);
		
		if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
		{
			aux_rev_sec = PILOTE_SPI.checa_parpadea_12AM ? 0 :PILOTE_SPI.OUT_BARRIDO[3];
			PILOTE_SPI.OUT_BARRIDO[3] |= aux_rev_sec;
		}
		
	}
	else
	{
		if(PILOTE_SPI.OUT_BARRIDO[3]!=0)
		PILOTE_SPI.OUT_BARRIDO[3]=0;
		
		if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
		{
			aux_rev_sec = PILOTE_SPI.checa_parpadea_12AM ? 0 :PILOTE_SPI.OUT_BARRIDO[3];
			PILOTE_SPI.OUT_BARRIDO[3] |= aux_rev_sec;
		}
	}
	/******************************************************************************/
	/**   OUTBARRIDO[4]                                                ************/
	
	PILOTE_SPI.tmp_acmd=PILOTE_HORLOGE.year;
	
	if(PILOTE_HORLOGE.year==0x00)
	{
		PILOTE_SPI.tmp_acmd=60;
	}

	if(PILOTE_SPI.tmp_acmd<=15)
	{
		
		//tmp_acmd= 32-tmp_acmd;
		
		//if(PILOTE_SPI.OUT_BARRIDO[4]!=CLR_UP)
		PILOTE_SPI.OUT_BARRIDO[4]=CLR_UP;                         //      1111 1111 1000 0000 0000 0000 0000 0000
		                                                          //      0000 0000 0000 0000 0000 0000 0000 0000
		PILOTE_SPI.OUT_BARRIDO[4]=PILOTE_SPI.OUT_BARRIDO[4]>>(16-PILOTE_SPI.tmp_acmd);
		PILOTE_SPI.OUT_BARRIDO[4]=PILOTE_SPI.OUT_BARRIDO[4]<<(1);
		PILOTE_SPI.OUT_BARRIDO[4]&=  0xFFFE0000;
		
		if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
		{
			aux_rev_sec= PILOTE_SPI.checa_parpadea_12AM ? 0 : 0xFFFE0000;
			PILOTE_SPI.OUT_BARRIDO[4] &= aux_rev_sec;
		}		
	}
	
	else
	
	{
		if(PILOTE_SPI.tmp_acmd!=60)
		{
			PILOTE_SPI.OUT_BARRIDO[4]= 0XFFFE0000;
			
			if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
			{
				
				PILOTE_SPI.OUT_BARRIDO[4] = PILOTE_SPI.checa_parpadea_12AM ? 0 : 0xFFFE0000;
				
			}
			
		}
		else
		{
			PILOTE_SPI.OUT_BARRIDO[4]= 0xFFFF0000;
			if(MODE_DEPLOYE.selectionner_mode==PRG_YR)
			{
				
				PILOTE_SPI.OUT_BARRIDO[4] = PILOTE_SPI.checa_parpadea_12AM ? 0 : 0xFFFF0000;				
				
			}
			
		}
	
	}
	
}


void Despliega()
{	
	if(PILOTE_SPI. recorre_barrido >0x10)// mayor que una quinta posicion binaria
	{
		PILOTE_SPI.recorre_barrido=0x1;
	}

    PORT_BARRIDO=0;	
	HC595Latch();
	DELAY_us(25);
	PORT_BARRIDO=PILOTE_SPI.recorre_barrido;
	PILOTE_SPI.recorre_barrido = PILOTE_SPI. recorre_barrido << 1;

} //end despliega


void send_spi(void)
{
	
	PILOTE_SPI.next_outbarrido++;
	
	if(PILOTE_SPI.next_outbarrido>4)
	PILOTE_SPI.next_outbarrido=0;
    

	PILOTE_SPI.tmp_spi = PILOTE_SPI.OUT_BARRIDO[PILOTE_SPI.next_outbarrido];
	PILOTE_SPI.tmp_spi2 = PILOTE_SPI.tmp_spi & 0b00000000000000000000000011111111;	
	PILOTE_SPI.spi_data[0] =PILOTE_SPI. tmp_spi2;


	PILOTE_SPI.tmp_spi=PILOTE_SPI. OUT_BARRIDO[PILOTE_SPI.next_outbarrido];
	PILOTE_SPI.tmp_spi2 = PILOTE_SPI.tmp_spi &0b00000000000000001111111100000000;	
	PILOTE_SPI.tmp_spi2= PILOTE_SPI.tmp_spi >> 8;		
	PILOTE_SPI.spi_data[1]=PILOTE_SPI.tmp_spi2;	
	
	
	PILOTE_SPI.tmp_spi= PILOTE_SPI.OUT_BARRIDO[PILOTE_SPI.next_outbarrido];	
	PILOTE_SPI.tmp_spi2=PILOTE_SPI.tmp_spi & 0b00000000111111110000000000000000;	
	PILOTE_SPI.tmp_spi2=PILOTE_SPI. tmp_spi >> 16;	
	PILOTE_SPI.spi_data[2]=PILOTE_SPI.tmp_spi2;
	
	
	PILOTE_SPI.tmp_spi=PILOTE_SPI.OUT_BARRIDO[PILOTE_SPI.next_outbarrido];
	PILOTE_SPI.tmp_spi = PILOTE_SPI.tmp_spi & 0b11111111000000000000000000000000;
	PILOTE_SPI.tmp_spi2= PILOTE_SPI.tmp_spi >> 24;	
	PILOTE_SPI.spi_data[3]=PILOTE_SPI.tmp_spi2;
	
	PILOTE_SPI.send_store= TRUE;

	
}
