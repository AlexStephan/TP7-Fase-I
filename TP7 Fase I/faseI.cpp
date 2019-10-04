/*
	DUDAS A RESOLVER:

	con S (Accompanies display shift) = 1 en la instruccion Entry mode set:
	-avanza de la 0F a la 10 o a la 40?
	-avanza de la 4F a la 00 o a la 50?
	-en caso de ser la seguna, shiftea el display?

	con S = 0:
	-avanza de la 0F a la 40 o a la 00? (simil 4F a 00 o 40)

	NOTA:
	-Estilo C? separar en .h y .c




*/

#include <iostream>
#include <cstdlib>

#include "ftd2xx.h"

typedef unsigned char BYTE;



//--------------------------------------------------------------//
// Asignacion de nombres a los pines del puerto
// (Nombramos los elementos fisicos)
#define PORT_P0 0
#define PORT_P1 1
#define PORT_P2 2
#define PORT_P3 3
#define PORT_P4 4
#define PORT_P5 5
#define PORT_P6 6
#define PORT_P7 7
#define PORT_P8 8

// Asignacion de funciones a los pines del puerto
// (asignacion funcional a cada bit fisico)
#define LCD_E	(1<<PORT_P0)
#define LCD_RS	(1<<PORT_P1)

#define LCD_D4	(1<<PORT_P4)
#define LCD_D5	(1<<PORT_P5)
#define LCD_D6	(1<<PORT_P6)
#define LCD_D7	(1<<PORT_P7)

// Mascaras
#define MASK_LCD	(LCD_E | LCD_RS | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7)
#define NOT_MASK_LCD	(~MASK_LCD)

// Definicion de niveles logicos (polaridad de los bits)
#define LCD_E_ON	(LCD_E)
#define LCD_E_OFF	(LCD_E ^ LCD_E)

#define LCD_RS_IR	(LCD_RS ^ LCD_RS)	//instrucciones	(0)
#define LCD_RS_DR	(LCD_RS)			//datos			(1)

//------------------------------------------------------------//

//Definicion de las instrucciones del LCD
//---------------------------------------

#define LCD_CLEAR	0x01
#define LCD_HOME	0x02

//Movimiento del cursor al realizarse una escritura
#define LCD_ENTRYSET_LEFT		0x04	//en ambos casos, S=0, es decir no se acompaña al shift del display
#define LCD_ENTRYSET_RIGHT		0x06
#define LCD_ENTRYSET_S_LEFT		0x05	//con acompañamiento del shift
#define LCD_ENTRYSET_S_RIGHT	0x07

#define LCD_CONTROL	0x08	//utilicese con las siguientes mascaras (empleando |, siempre una de cada par)
#define LCD_CTRL_DISPLAY_ON		(1 << 2)	//Prender/apagar el display
#define LCD_CTRL_DISPLAY_OFF	(0 << 2)
#define LCD_CTRL_CURSOR_ON		(1 << 1)	//Prender/apagar el cursor
#define LCD_CTRL_CURSOR_OFF		(0 << 1)
#define LCD_CTRL_BLINK_ON		(1 << 0)	//Encender/apagar parpadeo del cursor
#define LCD_CTRL_BLINK_OFF		(0 << 0)
//Ejemplo: (LCD_CONTROL | LCD_CTRL_DISPLAY_ON | LCD_CTRL_CURSOR_ON | LCD_CTRL_BLINK_OFF)

#define LCD_MOVE_LEFT	0x10		//Movimiento del cursor
#define LCD_MOVE_RIGHT	0x14

// setea address (posicion) del Display Data RAM
#define LCD_SET_ADD		0x80	//utilicese con las siguientes mascaras
#define LCD_FIRSTLINE	0x00	//Lineas ("filas" del LCD)
#define LCD_SECONDLINE	0x40
#define LCD_POS0		0x00	//Posicion del cursor ("Columnas")
#define LCD_POS1		0x01
#define LCD_POS2		0x02
#define LCD_POS3		0x03
#define LCD_POS4		0x04
#define LCD_POS5		0x05
#define LCD_POS6		0x06
#define LCD_POS7		0x07
#define LCD_POS8		0x08
#define LCD_POS9		0x09
#define LCD_POS10		0x0A
#define LCD_POS11		0x0B
#define LCD_POS12		0x0C
#define LCD_POS13		0x0D
#define LCD_POS14		0x0E
#define LCD_POS15		0x0F
//Ejemplo:	(LCD_SET_ADD | LCD_SECONDLINE | LCD_POS12)
//o, de forma equivalente:
//			(LCD_SET_ADD | LCD_SECONDLINE | 12)

#define LSB(x)	((x)&0x0F)
#define MSB(x)	(((x)&0xF0)>>4)
//Uno q bit a bit separe el BYTE en los correspondientes pines

typedef struct FT_HANDLE_	FT_HANDLE;

FT_HANDLE* lcdInit(int iDevice);
void lcdWriteIR(FT_HANDLE* deviceHandler, BYTE valor);
void lcdWriteDR(FT_HANDLE* deviceHandler, BYTE valor);

static void lcdWriteNibble(FT_HANDLE* deviceHandler, BYTE valor);
static void lcdWriteByte(FT_HANDLE* deviceHandler, BYTE valor, BYTE rs);


void lcdWriteIR(FT_HANDLE* deviceHandler, BYTE valor) {
	lcdWriteByte(deviceHandler, valor, LCD_RS_IR);
}
void lcdWriteDR(FT_HANDLE* deviceHandler, BYTE valor) {
	lcdWriteByte(deviceHandler, valor, LCD_RS_DR);
}

static void lcdWriteByte(FT_HANDLE* deviceHandler, BYTE valor, BYTE rs) {

}