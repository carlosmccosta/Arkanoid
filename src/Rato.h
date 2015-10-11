/**\file Rato.h
 * \brief Módulo com as subrotinas necessárias para o uso do rato durante o jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Rato.h \n
 * DESCRIÇÃO: Módulo com as subrotinas necessárias para o uso do rato durante o jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef RATO_H_
#define RATO_H_

#include "GraficaVideo.h"
#include "KBC.h"
#include "Interrupcoes.h"
#include "Sprite.h"
#include "GQueue.h"
#include "Teclado.h"
#include <dpmi.h>

#define MOUSE_ISR_SELECT 1

void lock_mouse_isr();
void lock_mouse_isr_gqueue();


typedef struct {
	Byte MSByte1;
	Byte MSByte2;
	Byte MSByte3;
	int dx;
	int dy;
	int xov;
	int yov;
	int lmb;
	int rmb;
	int mmb;
	Bool mouse_move;
} MouseState;


struct mousedata
{
	Byte Byte1;
	Byte Byte2;
	Byte Byte3;
}__attribute__((__packed__));

typedef struct mousedata MouseData;

extern volatile unsigned char mouse_byte1;
extern volatile unsigned char mouse_byte2;
extern volatile unsigned char mouse_byte3;
extern volatile unsigned char pack_completo;

extern GQueue *mouse_queue;
extern volatile MouseState mouse_state;


///Funcao que inicializa o rato
int mouse_init(int debug);

///Funçao restora a isr que estava antes de instalar a nossa implementada
void restore_mouse_isr();
void restore_mouse_isr_gqueue();

/** Disable the mouse, sending a StreamDisable to the mouse, then
 * disables generation of mouse interrupts at the KBC, sends a
 * DisableMouse to the KBC and finnaly disable mouse interrupts at the
 * PIC2
 */
void mouse_disable();

///função que analisa os 3 bytes que o rato manda
///usa variaveis volateis
void parse_mouse_event();

///função que analisa os 3 bytes que o rato manda
///usa uma gqueue
void parse_mouse_event_gqueue();


#endif
