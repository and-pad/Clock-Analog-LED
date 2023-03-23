#ifndef _interrupts_H
#define _interrupts_H


#include <avr/io.h>
#include <avr/interrupt.h>
#include "rtc_ds1307.h"
//puerto 595
#define HC595_PORT           PORTA
#define HC595_DDR             DDRA
#define HC595_OE_POS      PA3

#define STORE    0b00000010
#define MASK595  STORE
#define HC595_ST_CP_POS PA1


//puerto barrido uln
#define PORT_BARRIDO PORTB
#define DDR_BARRIDO DDRB

//define mosi y sck
#define SCK  PB7
#define MOSI PB5

typedef  struct 
{
		
uint8_t recorre_barrido;
uint32_t OUT_BARRIDO[5];
uint8_t spi_data[4];
uint32_t tmp_spi;
uint32_t tmp_spi2;
uint8_t send_store;
uint8_t next_outbarrido;
uint8_t barrer;
uint8_t enviar_nuevo;
uint8_t tmp_acmd;
uint32_t temp_32_SH;

uint8_t checa_parpadea_12AM ;

}SPI;



SPI PILOTE_SPI;

#define NUM_SALIDAS 32
#define MOD_S1 52
#define CLR_UP 0xFFFFFFFF
#define NUM_MIN 60
#define CERO 0


/*************Define Prototypes*****************/
unsigned char BCDaDecimal(unsigned char bcdByte);
uint8_t DecimalToBCD (uint8_t decimalByte);
void HC595Latch(void);
void Despliega(void);
void send_spi(void);
void Acomoda_5x32(void);
void Acomoda_5X32_DATE(void);
void LeeRTC(void);

void Modulo_Brillo(void);
/***********************************************/


#endif