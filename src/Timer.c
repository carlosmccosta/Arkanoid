/**\file Timer.c
 * \brief Módulo que permitirá a manipulação do timer
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Timer.c \n
 * DESCRIÇÃO: Módulo que permitirá a manipulação do timer \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Timer.h"

void t0_isr(void);
void lock_t0_isr() { _go32_dpmi_lock_code(t0_isr, (unsigned long)(lock_t0_isr - t0_isr)); }
//int mil_tick;
//int sec_tick;


void timer_init(int timer, int mode)
{
	outportb(TIMER_CTRL,(timer<<6)|mode);
	outportb(SPEAKER_CTRL,inportb(SPEAKER_CTRL)|TIMER2_ENABLE);
}


void timer_load(int timer, int value)
{
	outportb(TIMER_0|timer, LSB(value));
	outportb(TIMER_0|timer, MSB(value));
}


_go32_dpmi_seginfo prev_isr;

void timer0_init() {
	disable_irq(0);
	
	lock_t0_isr();
	
	timer_init(TIMER_0, MODE2|LSBMSB);
	timer_load(0, TIMER_CLK/1000);
	set_isr(0,t0_isr, & prev_isr);
	enable_irq(0);

}

void restore_timer0() {
	restore_isr(0,& prev_isr);
}



void mili_sleep(int mili)
{
	int val = TIMER_CLK / 1000.0;

	timer_load(0, val);
	mil_tick = 0;

	_go32_dpmi_seginfo old_irq;
	set_isr(T0_IRQ, t0_isr, &old_irq);

	while(mil_tick < mili) {}

	restore_isr(T0_IRQ, &old_irq);
}


void sec_sleep(int secs)
{
	mili_sleep(secs*1000);
}
