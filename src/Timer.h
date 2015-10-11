/**\file Timer.h
 * \brief Módulo que permitirá a manipulação do timer
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Timer.h \n
 * DESCRIÇÃO: Módulo que permitirá a manipulação do timer \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#ifndef TIMER_H_
#define TIMER_H_

#include <go32.h>
#include <sys/farptr.h>
#include <sys/nearptr.h>
#include <pc.h>
#include <dos.h>
#include <stdio.h>

#include "utypes.h"
#include "Interrupcoes.h"


 // protótipo do novo handler, escrito em assembly
void t0_isr(void);
void lock_t0_isr();

extern volatile int mil_tick;
extern volatile int sec_tick;

/** @name Timer port numbers */
/*@{*/
#define TIMER_0      0x40 ///< Timer0 address
#define TIMER_1      0x41 ///< Timer1 address
#define TIMER_2      0x42 ///< Timer2 address
#define TIMER_CTRL   0x43 ///< Timer control register address 
/*@}*/

/** @name Speaker and Timer2 control */
/*@{*/
#define SPEAKER_CTRL    0x61    ///< Port number of PC register whose bits 0 and 1 control TIMER_2  and the output to the speaker
#define TIMER2_ENABLE  (1 << 0) ///< Enable Timer2, bit 0 to 1
#define SPEAKER_ENABLE (1 << 1) ///< Enable output to speaker, bit 1 to 1
/*@}*/

/** @name Some useful definitions for timer programming */
/*@{*/
#define TIMER_CLK    1193181 	///< Frequência de entrada dos timers

#define LSBMSB       0x30       ///< LSB followed by MSB
#define MODE2	     0x04       ///< Counting mode 2: freq. div (impulse)
#define MODE3        0x06       ///< Counting mode 3: freq. div (square wave)
#define BCD          0x01       ///< BCD counter
#define LSB(i) ((i) & 0xFF)
#define MSB(i) ((i) >> 8)

#define HLT __asm__ __volatile__ ("HLT")
/*@}*/

/** Program timer (0,1,2) with mode
 */
void timer_init(int timer, int mode);

/** Load timer (0,1,2) with value
 */
void timer_load(int timer, int value);

void timer0_init();

void restore_timer0();

/** Wait mili miliseconds, indirectly counting T0 interrupts
*/
void mili_sleep(int mili);

/** wait secs seconds, indirectly counting T0 interrupts
 */
void sec_sleep(int secs);

/** @} end of TimerCounter */



#endif
