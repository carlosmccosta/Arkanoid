/**\file Teclado.h
 * \brief Módulo que possibilitará o uso do teclado por parte do utilizador nos menus
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Teclado.h \n
 * DESCRIÇÃO: Módulo que possibilitará o uso do teclado por parte do utilizador nos menus \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef TECLADO_H_
#define TECLADO_H_

#include "KBC.h"
#include "Queue.h"
#include "Interrupcoes.h"

typedef enum {  SC_A=0x1E,
				SC_B=0x30,
				SC_C=0x2E,
				SC_D=0x20,
				SC_E=0x12,
				SC_F=0x21,
				SC_G=0x22,
				SC_H=0x23,
				SC_I=0x17,
				SC_J=0x24,
				SC_K=0x25,
				SC_L=0x26,
				SC_M=0x32,
				SC_N=0x31,
				SC_O=0x18,
				SC_P=0x19,
				SC_Q=0x10,
				SC_R=0x13,
				SC_S=0x1F,
				SC_T=0x14,
				SC_U=0x16,
				SC_V=0x2F,
				SC_W=0x11,
				SC_X=0x2D,
				SC_Y=0x15,
				SC_Z=0x2C,

				SC_1=0x02,
				SC_2=0x03,
				SC_3=0x04,
				SC_4=0x05,
				SC_5=0x06,
				SC_6=0x07,
				SC_7=0x08,
				SC_8=0x09,
				SC_9=0x0A,
				SC_0=0x0B,

				SC_F1=0x3B,
				SC_F2=0x3C,
				SC_F3=0x3D,
				SC_F4=0x3E,
				SC_F5=0x3F,
				SC_F6=0x40,
				SC_F7=0x41,
				SC_F8=0x42,
				SC_F9=0x43,
				SC_F10=0x44,
				SC_F11=0x85,
				SC_F12=0x86,

				SC_ESC=0x01,
				SC_ENTER=0x1C,
				SC_SPACE=0x39,
				SC_UP=0x48,
				SC_DOWN=0x50,
				SC_LEFT=0x4B,
				SC_RIGHT=0x4D
} SC_ID;

void lock_kbd_isr();

extern Queue keys_queue;

void kbd_init();

///Funçao que modifica o isr invocando a funçao set_isr
void set_kbd_isr();

///Funçao restora a isr que estava antes de instalar a nossa implementada
void restore_keyboard_isr();

/** shortky blink all three keyboard LEDs
 *
 */
void blink_leds();

/** shortky blink left(1), middle(2) or right(3) keyboard LED
 *
 */
void blink_led(uchar led);

#endif
