/**\file Interrupcoes.h
 * \brief Base de dados de sons que serão usados durante o jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Interrupcoes.h \n
 * DESCRIÇÃO: Base de dados de sons que serão usados durante o jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */

#ifndef INTERRUPCOES_H_
#define INTERRUPCOES_H_

#include <pc.h>
#include <dos.h>
#include <dpmi.h>
#include <go32.h>
#include "utypes.h"



/** @name PIC registers address */
/*@{*/
#define EOI       0x20  ///< End Of Interrupt Command */
#define PIC1_CMD  0x20  ///< PIC1 register address to send EOI */
#define PIC2_CMD  0xA0  ///< PIC2 register address to send EOI */
#define PIC1_MASK 0x21  ///< PIC1 register address to read/write interrupt mask */
#define PIC2_MASK 0xA1  ///< PIC2 register address to read/write interrupt mask */
/*@}*/


/** @name PC Interrupts */
/*@{*/
#define T0_IRQ    0  ///< Timer 0
#define KBD_IRQ   1  ///< keyboard
#define COM2_IRQ  3  ///< serial port 2
#define COM1_IRQ  4  ///< serial port 1
#define FLP_IRQ   6  ///< floppy
#define LPT_IRQ   7  ///< parallel port
#define RTC_IRQ   8  ///< realtime clock
#define MOUSE_IRQ 12 ///< mouse
#define FPU_IRQ   13 ///< Floating point
#define DISK1_IRQ 14 ///< Hard disk controller 1
#define DISK2_IRQ 15 ///< Hard disk controller 2

#define PIC1_EN_PIC2_INTS 2
#define PIC2_EN_PIC2_INTS 9
/*@}*/

/** @name Some usefull definitions */
/*@{*/
/** Gives mask bit associated with a given irq.
 * <em>Warning</em>, if irq > 7 the result must be applied to PIC2
 */
#define IRQ_MASK_BIT(irq) ((irq) < 8 ? 1 << (irq) : (1 << (irq)) >> 8)

/** gives the vector associated with a given IRQ */
#define IRQ_VECTOR(irq) ((irq) < 8 ? (irq) + 0x08 : (irq) - 8 + 0x70)
/*@}*/


#define IRQ_MASK(irq) ((irq)< 8 ? 1 << (irq) : (1 << (irq)) >> 8)
#define PIC1_MASK 0x21  ///< PIC1 interrupt mask register */
#define PIC2_MASK 0xA1  ///< PIC2 interrupt mask register */


/** gives the vector associated with a given IRQ */
int irq_vector(int irq);

/** Modificate the interrupt handler specified in 'prev_isr' for interrupt
 * 'irq'. 
 */
int set_isr(int irq, void (*isr)(void), _go32_dpmi_seginfo *prev_isr);

void restore_isr(int irq, _go32_dpmi_seginfo *isr);

int set_isr_c_wrapper(int irq, void (*isr)(void), _go32_dpmi_seginfo *prev_isr);

void restore_isr_c_wrapper(int irq, _go32_dpmi_seginfo *isr);


/** Unmask the bit corresponding to 'irq', enabling its interrupts.
 * The correct PIC is used.
*/
void enable_irq(int irq);

/** Mask the bit corresponding to 'irq', disabling its interrupts.
 * Returns the previous irq status
 * The correct PIC is used.
 */
void disable_irq(int irq);


//activar/desactivar interrupcoes globalmente
void set_ints(Bool on);


Byte get_pic1();
Byte get_pic2();
void set_pic_var(Byte pic1, Byte pic2);
void mask_pic(int irq);
void unmask_pic(int irq);
void mask_pic_var(int irq, Byte* pic1, Byte* pic2);
void unmask_pic_var(int irq, Byte* pic1, Byte* pic2);

/** @} end of interrupts */



#endif
