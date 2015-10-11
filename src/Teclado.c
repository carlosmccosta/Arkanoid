/**\file Teclado.c
 * \brief Módulo que possibilitará o uso do teclado por parte do utilizador nos menus
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Teclado.c \n
 * DESCRIÇÃO: Módulo que possibilitará o uso do teclado por parte do utilizador nos menus \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Teclado.h"

void kbd_isr();
void lock_kbd_isr() { _go32_dpmi_lock_code(kbd_isr, (unsigned long)(lock_kbd_isr - kbd_isr)); }

Queue keys_queue;


void kbd_init() {
	disable_irq(KBD_IRQ);
	queueInit(&keys_queue);
	
	lock_kbd_isr();
	_go32_dpmi_lock_data((void *)&keys_queue, sizeof(Queue));
	lock_queuePut();
	lock_queueFull();
	
	set_isr(KBD_IRQ, kbd_isr, &prev_kbd_isr);
	enable_irq(KBD_IRQ);	
}

void set_kbd_isr() {
	set_isr(KBD_IRQ, kbd_isr, &prev_kbd_isr);
}

void restore_keyboard_isr() {
	disable_irq(KBD_IRQ);
	restore_isr(KBD_IRQ, &prev_kbd_isr);
	enable_irq(KBD_IRQ);
}


void blink_leds() {
	enable_irq(KBD_IRQ);
	enable_irq(MOUSE_IRQ);

	write_kbc_data_arg(WriteLEDS, SCROLL_LOCK | NUM_LOCK | CAPS_LOCK);
	mili_sleep(200);
	write_kbc_data_arg(WriteLEDS, 0);

	disable_irq(KBD_IRQ);
	disable_irq(MOUSE_IRQ);
}

void blink_led(uchar led) {
	enable_irq(KBD_IRQ);
	enable_irq(MOUSE_IRQ);

	write_kbc_data_arg(WriteLEDS, 1 << (led % 3));
	mili_sleep(200);
	write_kbc_data_arg(WriteLEDS, 0);

	disable_irq(KBD_IRQ);
	disable_irq(MOUSE_IRQ);
}
