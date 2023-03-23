/*
 * Plays_Externs.c
 *
 * Created: 28/09/2018 02:20:48 p. m.
 *  Author: Andres Padilla
 */ 
#include "interrupts.h"
#include "Plays_Externs.h"
#include <string.h>

void PLAYS(void)
{


/*
 Drive_ornament.contador_vueltas++;

	Drive_ornament.nivel_brillo=0;
	switch(Drive_ornament.nivel_brillo)
	    {
		case 0:
		
		if(Drive_ornament.contador_vueltas<100)
			{
				PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
				PILOTE_SPI.OUT_BARRIDO[4]|= 0xFFFF;				
		
			}
         else
			{
				PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
				PILOTE_SPI.OUT_BARRIDO[4]|=0;
				
				if(Drive_ornament.contador_vueltas==101)
				{
					Drive_ornament.contador_vueltas=0;					
				}				
			}
			break;

			}

*/



///******mis mamadas********
switch(Drive_ornament.select_game)
{
	
	case 0:	
	 
	 if (Drive_ornament.i>Drive_ornament.how_loops)
		{		
		Drive_ornament.select_game++;
		Drive_ornament.i=0;
		Drive_ornament.how_loops=30;
		}
		
	if(Drive_ornament.past_exec!=Drive_ornament.execute_mov)
	{		
		switch (Drive_ornament.execute_mov)
		{
			
			case 0:
				PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
				PILOTE_SPI.OUT_BARRIDO[4]|= 0x80;
				
			break;
			
			case 1:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x4;
			break;
			
			case 2:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x20;
			
			break;
			
			case 3:
			
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x1;
			
			
			break;
			
			case 4: 
			
			PILOTE_SPI.OUT_BARRIDO[4]&= 0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x8000;	
			
			break;
			
			case 5:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x400;
			
			break;
			
			case 6:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x2000;			
			break;
			
			case 7:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x100;
			break;
			
			case 8:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x8;
			break;
			
			case 9:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x40;
			break;
			
			case 10:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x2;
			break;
			
			case 11:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x10;
			break;
			
			case 12:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x800;
			break;
			
			case 13:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x4000;
			break;
			
			case 14:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x200;
			break;
			
			case 15:
			PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
			PILOTE_SPI.OUT_BARRIDO[4]|= 0x1000;
			Drive_ornament.execute_mov=255;
			
			Drive_ornament.past_exec=Drive_ornament.execute_mov;
			Drive_ornament.i++;
			break;
							
			//case 16:
		
		/*	Drive_ornament.execute_mov=255;
			
			Drive_ornament.past_exec=Drive_ornament.execute_mov;
			Drive_ornament.i++;
			*/
	     	//break;
			 	
		}
			
	  break;
			
			case 1:
		
			if (Drive_ornament.i>Drive_ornament.how_loops)
			{
			//Drive_ornament.select_game++;
			Drive_ornament.i=0;
			
			Drive_ornament.select_game=0;
			Drive_ornament.how_loops=20;
			}
			
			if(Drive_ornament.past_exec!=Drive_ornament.execute_mov)
			{
				
				switch (Drive_ornament.execute_mov)
				{
					
					case 0:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x80;
					
					break;
					
					case 1:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x4;
					break;
					
					case 2:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x20;
					
					break;
					
					case 3:
					
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x1;
					
					
					break;
					
					case 4:
					
					PILOTE_SPI.OUT_BARRIDO[4]&= 0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x8000;
					
					break;
					
					case 5:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x400;
					
					break;
					
					case 6:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x2000;
					break;
					
					case 7:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x100;
					break;
					
					case 8:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x8;
					break;
					
					case 9:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x40;
					break;
					
					case 10:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x2;
					break;
					
					case 11:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x10;
					break;
					
					case 12:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x800;
					break;
					
					case 13:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x4000;
					break;
					
					case 14:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x200;
					break;
					
					case 15:
					PILOTE_SPI.OUT_BARRIDO[4]&=0xFFFF0000;
					PILOTE_SPI.OUT_BARRIDO[4]|= 0x1000;
					Drive_ornament.execute_mov=255;
					
					Drive_ornament.past_exec=Drive_ornament.execute_mov;
					Drive_ornament.i++;
					break;
					
				
				}
			
			}
			
			break;
	}
	

	
 }




}