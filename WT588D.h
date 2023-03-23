/*
 * WT588D.h
 *
 * Created: 30/09/2018 11:17:55 p. m.
 *  Author: andre
 */ 


#ifndef WT588D_H_
#define WT588D_H_
#include <avr/io.h>

#define PORT_DRV_WT588_RST       PORTA
#define PORT_DRV_WT588_ALLNO_RST PORTC
#define PORT_IN_BUSY             PINA

#define RST_WT588   0b00000001
#define BUSY_WT588  0b00000100

#define DAT_WT588    0b00010000
#define CS_WT588     0b00100000
#define CLOCK_WT588  0b01000000
/*
#define SOUND_ALARMA                                 0x0  //HATENO ALARMA
#define SOUND_ALARMA2                               0x6  //GERUDO ALARMA
#define SOUND_MOVE_SETTINGS                0x1 //MENU MOVE
#define SOUND_ENTER_SETTINGS              0x2 //MENU OPEN
#define SOUND_MORNING                            0x3 //morning theme
#define SOUND_NIGHT                                 0x4 //wolfs  & crows
#define SOUND_MENU_CLOSE                     0x5// 
#define SOUND_FANFARE                             0x7
#define SOUND_SECRET                               0x8
#define SOUND_BRILLO                                0x9
#define SOUND_ALARMA3                           0xA// ZELDA 8bits
#define SOUND_RUPEE                                0xB//
#define SOUND_STOP                                  0xFE//STOP
*/

#define SOUND_ALARMA                                 0x0  //delfino plaza
#define SOUND_ALARMA2                               0x1  //pinguino n64
#define SOUND_ALARMA3                               0x2// ending mario3
#define SOUND_ENTER_SETTINGS               0x3 //pause
#define SOUND_MOVE_SETTINGS                0x4 //fireball
#define SOUND_MENU_CLOSE                       0x5// pipe
#define SOUND_FANFARE                               0x6//salida planta
#define SOUND_SECRET                                 0x7//1 vida
#define SOUND_BRILLO                                 0x8//agarrar bandera
#define SOUND_STOP                                  0xFE//STOP


typedef struct
    {	
		uint8_t rola;
		uint8_t rota_rola;
		uint8_t comp_rola;
		
		uint8_t i;
		uint8_t send_audio;
		
		uint8_t on_timer;
		
		uint8_t contador_ms;
		uint8_t suma_ms;
		uint8_t contador_us;
		
		uint8_t time_off_secuence;
		
		uint8_t protocol_part;
		
		uint8_t check_how_ms;
		
		
	   uint8_t alarma;
	   uint8_t sonidos_general;
	}WT588D;
	
	
	typedef struct{
		uint8_t alarm;
		//uint8_t ornaments;
		uint8_t sounds;
//		uint8_t dianoche;
		
		}ACTIVE;

WT588D Drive_WT58;
ACTIVE On_Off_Options;

void play_song_secuence(void);
void on_audio(uint8_t rola);
void on_audio_alrm(uint8_t rola);
void Execute_audio(uint8_t rola);
#endif /* WT588D_H_ */