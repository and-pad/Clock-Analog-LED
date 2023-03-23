/*
 * Play_Externs.h
 *
 * Created: 28/09/2018 02:21:29 p. m.
 *  Author: andre
 */ 


#ifndef PLAYS_EXTERNS_H_
#define PLAYS_EXTERNS_H_



typedef struct  
{
		
	
	uint8_t nivel_brillo;
	uint8_t contador_vueltas;
	uint8_t contador_us;
	uint16_t tiempo_entre_brillos;
	
	// variables de mis mamadas 
	uint8_t execute_mov;
	uint8_t past_exec;	
	uint8_t num_times_count;
	uint8_t i;
	
	uint8_t select_game;
	
	uint8_t how_loops;
	
	
}ornament;

ornament Drive_ornament;


///prototipos*************//////
void PLAYS(void);


#endif /* PLAY_EXTERNS_H_ */

