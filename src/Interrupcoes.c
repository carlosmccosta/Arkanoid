/**\file Interrupcoes.c
 * \brief Base de dados de sons que serão usados durante o jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Interrupcoes.c \n
 * DESCRIÇÃO: Base de dados de sons que serão usados durante o jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
 
#include "Interrupcoes.h"

//Desabilitar memória virtual
#include <crt0.h>
int _crt0_startup_flags = _CRT0_FLAG_LOCK_MEMORY;


//Usado nos locks do código ou dados para evitar page faults
//http://www.delorie.com/djgpp/doc/ug/interrupts/inthandlers2.html
#define END_OF_FUNCTION(x) void x##_end() { }
#define LOCK_VARIABLE(x) _go32_dpmi_lock_data((void *)&x, sizeof(x))
#define LOCK_FUNCTION(x) _go32_dpmi_lock_code(x, (long)x##_end - (long)x)


int irq_vector(int irq)
{
	if (irq< 8)
		irq = irq + 0x08;
	else
		irq = irq+0x70-8;
	return irq;
}


int set_isr(int irq, void (*isr)(void), _go32_dpmi_seginfo *prev_isr){
	int vector = irq_vector(irq);
	if(_go32_dpmi_get_protected_mode_interrupt_vector(vector, prev_isr))
		return -1;

	_go32_dpmi_seginfo new_isr;
	new_isr.pm_selector = _go32_my_cs();
	new_isr.pm_offset=(unsigned long) isr;

	if(_go32_dpmi_set_protected_mode_interrupt_vector(vector, &new_isr))
		return -1;

	return 0;

}

void restore_isr(int irq, _go32_dpmi_seginfo *isr){
	int vector = irq_vector(irq);
	_go32_dpmi_set_protected_mode_interrupt_vector(vector, isr);
}


int set_isr_c_wrapper(int irq, void (*isr)(void), _go32_dpmi_seginfo *prev_isr) {

	int vector = irq_vector(irq);
	if(_go32_dpmi_get_protected_mode_interrupt_vector(vector, prev_isr))
		return -1;

	_go32_dpmi_seginfo new_isr;
	new_isr.pm_selector = _go32_my_cs();
	new_isr.pm_offset=(unsigned long) isr;

	/* prepara função assembly para chamar função C */
	_go32_dpmi_allocate_iret_wrapper(&new_isr);

	if(_go32_dpmi_set_protected_mode_interrupt_vector(vector, &new_isr))
		return -1;

	return 0;
}

void restore_isr_c_wrapper(int irq, _go32_dpmi_seginfo *isr) {
	int vector = irq_vector(irq);
	_go32_dpmi_set_protected_mode_interrupt_vector(vector, isr);
}

void enable_irq(int irq){

	unsigned short pic;
	if(irq<8)
		pic=PIC1_MASK;
	else
		pic=PIC2_MASK;
	unsigned char mask = inportb(pic) &(~IRQ_MASK(irq));
	outportb(pic, mask);

}

void disable_irq(int irq){

	unsigned short pic;
	if(irq<8)
		pic=PIC1_MASK;
	else
		pic=PIC2_MASK;
	unsigned char mask = inportb(pic) | (IRQ_MASK(irq));
	outportb(pic,mask);

}


void set_ints(Bool on)
{
	static Byte state_pic1;
	static Byte state_pic2;
	
	if(on)
	{
		outportb(PIC1_MASK, state_pic1);
		outportb(PIC2_MASK, state_pic2);
	}
	else
	{
		state_pic1 = inportb(PIC1_MASK);
		state_pic2 = inportb(PIC2_MASK);
		outportb(PIC1_MASK, 0xFF);
		outportb(PIC2_MASK, 0xFF);
	}
}


Byte get_pic1() {
	return inportb(PIC1_MASK);
}


Byte get_pic2() {
	return inportb(PIC2_MASK);
}


void set_pic_var(Byte pic1, Byte pic2)
{
	outportb(PIC1_MASK, pic1);
	outportb(PIC2_MASK, pic2);
}


void mask_pic(int irq) {
  int tmp;
  if(irq<8) {
    tmp = inportb(PIC1_MASK);
    tmp = tmp | IRQ_MASK_BIT(irq);
    outportb(PIC1_MASK, tmp);
  }
  else {
    tmp = inportb(PIC2_MASK);
    tmp = tmp | IRQ_MASK_BIT(irq);
    outportb(PIC2_MASK, tmp);	
  }
}

void unmask_pic(int irq) {
  int tmp;
  if(irq<8) {
    tmp = inportb(PIC1_MASK);
    tmp = tmp & ~(IRQ_MASK_BIT(irq));
    outportb(PIC1_MASK, tmp);
  }
  else {
    tmp = inportb(PIC2_MASK);
    tmp = tmp & ~(IRQ_MASK_BIT(irq));
    outportb(PIC2_MASK, tmp);	
  }
}

void mask_pic_var(int irq, Byte* pic1, Byte* pic2)
{
	Byte* pic;
	
	if (irq < 8) pic = pic1;
	else pic = pic2;
	
	(*pic) |= IRQ_MASK_BIT(irq);
}


void unmask_pic_var(int irq, Byte* pic1, Byte* pic2)
{
	Byte* pic;
	
	if (irq < 8) pic = pic1;
	else pic = pic2;
	
	(*pic) &= (~IRQ_MASK_BIT(irq));
}
