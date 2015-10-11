/**\file Rato.c
 * \brief Módulo com as subrotinas necessárias para o uso do rato durante o jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: Rato.c \n
 * DESCRIÇÃO: Módulo com as subrotinas necessárias para o uso do rato durante o jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "Rato.h"

void mouse_isr();
void mouse_isr_end();
void lock_mouse_isr() { _go32_dpmi_lock_code(mouse_isr, (unsigned long)(lock_mouse_isr - mouse_isr)); }

void mouse_isr_gqueue();
void mouse_isr_gqueue_end();
void lock_mouse_isr_gqueue() { _go32_dpmi_lock_code(mouse_isr, (unsigned long)(lock_mouse_isr_gqueue - mouse_isr_gqueue)); }

volatile MouseState mouse_state = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

GQueue *mouse_queue = 0;


int mouse_init(int debug) {
	disable_irq(MOUSE_IRQ);
	//Bool has_mouse = kbc_init(debug);
	//0 -> gqueue
	if (MOUSE_ISR_SELECT == 0) {
		mouse_queue = newGQueue(50, sizeof(MouseData));
		
		lock_mouse_isr_gqueue();
		_go32_dpmi_lock_code(mouse_isr_gqueue, (unsigned long)(mouse_isr_gqueue_end - mouse_isr_gqueue));
		_go32_dpmi_lock_data((void *)mouse_queue, sizeof(GQueue));
		lock_putGQueue();
		lock_isFullGQueue();
		_go32_dpmi_lock_data((void *)&mouse_state, sizeof(MouseState));
		
		set_isr(MOUSE_IRQ, mouse_isr_gqueue, &prev_mouse_isr);
	} else {	
		lock_mouse_isr();
		_go32_dpmi_lock_code(mouse_isr_gqueue, (unsigned long)(mouse_isr_end - mouse_isr));
		_go32_dpmi_lock_data((void *)&mouse_state, sizeof(MouseState));
		
		set_isr(MOUSE_IRQ, mouse_isr, &prev_mouse_isr);
	}
	
	enable_irq(MOUSE_IRQ);
	
	//return has_mouse;
	return 1;
}

void restore_mouse_isr() {
	disable_irq(MOUSE_IRQ);
	restore_isr(MOUSE_IRQ, &prev_mouse_isr);
	enable_irq(MOUSE_IRQ);
}

void restore_mouse_isr_gqueue() {
	disable_irq(MOUSE_IRQ);
	restore_isr(MOUSE_IRQ, &prev_mouse_isr);
	enable_irq(MOUSE_IRQ);

	deleteGQueue(mouse_queue);
}


void mouse_disable() {
	write_aux(StreamDisable);

	write_kbc_cmd(ReadCommand);
	write_kbc_cmd_arg(WriteCommand, read_kbc() & ~(INT_12 | EN_MOUSE));

	write_kbc_cmd(DisableMouse);
	disable_irq(MOUSE_IRQ);
}

void parse_mouse_event() {
	if (pack_completo == 0) {
		mouse_state.MSByte1 = 0;
		mouse_state.MSByte2 = 0;
		mouse_state.MSByte3 = 0;
		mouse_state.dx = 0;
		mouse_state.dy = 0;
		mouse_state.xov = 0;
		mouse_state.yov = 0;
		mouse_state.lmb = 0;
		mouse_state.mmb = 0;
		mouse_state.rmb = 0;
		return;
	}

	disable_irq(MOUSE_IRQ);
	int dx, dy;
	mouse_state.MSByte1 = mouse_byte1;
	mouse_state.MSByte2 = mouse_byte2;
	mouse_state.MSByte3 = mouse_byte3;
	enable_irq(MOUSE_IRQ);
	
	dx = mouse_state.MSByte1 & XSGN ? (mouse_state.MSByte2 - 256) : mouse_state.MSByte2;
	dy = mouse_state.MSByte1 & YSGN ? (mouse_state.MSByte3 - 256) : mouse_state.MSByte3;
	mouse_state.xov = X_OVERFLOW(mouse_state.MSByte1);
	mouse_state.yov = Y_OVERFLOW(mouse_state.MSByte1);
	mouse_state.lmb = LEFT_BUTTON(mouse_state.MSByte1);
	mouse_state.mmb = MIDDLE_BUTTON(mouse_state.MSByte1);
	mouse_state.rmb = RIGHT_BUTTON(mouse_state.MSByte1);

	Bool move = true;
	if (mouse_state.xov || mouse_state.yov) {
		move = false;
	} else if ((dx != mouse_state.dx) || (dx != mouse_state.dy)) {
		move = true;
	}

	mouse_state.mouse_move = move;
	mouse_state.dx = dx;
	mouse_state.dy = dy;
}

void parse_mouse_event_gqueue() {
	MouseData* package = (MouseData*) getGQueue(mouse_queue);

	//Se não houver elementos na Gqueue, o rato não se mexeu
	if (package == NULL) {
		mouse_state.MSByte1 = 0;
		mouse_state.MSByte2 = 0;
		mouse_state.MSByte3 = 0;
		mouse_state.dx = 0;
		mouse_state.dy = 0;
		mouse_state.xov = 0;
		mouse_state.yov = 0;
		mouse_state.lmb = 0;
		mouse_state.mmb = 0;
		mouse_state.rmb = 0;
		return;
	}

	int dx, dy;
	mouse_state.MSByte1 = package->Byte1;
	mouse_state.MSByte2 = package->Byte2;
	mouse_state.MSByte3 = package->Byte3;
	dx = package->Byte1 & XSGN ? (package->Byte2 - 256) : package->Byte2;
	dy = package->Byte1 & YSGN ? (package->Byte3 - 256) : package->Byte3;
	mouse_state.xov = X_OVERFLOW(package->Byte1);
	mouse_state.yov = Y_OVERFLOW(package->Byte1);
	mouse_state.lmb = LEFT_BUTTON(package->Byte1);
	mouse_state.mmb = MIDDLE_BUTTON(package->Byte1);
	mouse_state.rmb = RIGHT_BUTTON(package->Byte1);

	Bool move = true;
	if (mouse_state.xov || mouse_state.yov) {
		move = false;
	} else if ((dx != mouse_state.dx) || (dx != mouse_state.dy)) {
		move = true;
	}

	mouse_state.mouse_move = move;
	mouse_state.dx = dx;
	mouse_state.dy = dy;

}

