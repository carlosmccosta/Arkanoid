/**\file KBC.c
 * \brief Módulo que contem as funções que activam/desactivam as interrupções provenientes do teclado.
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: KBC.c \n
 * DESCRIÇÃO: Módulo que contem as funções que activam/desactivam as interrupções provenientes do teclado. \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "KBC.h"

_go32_dpmi_seginfo prev_mouse_isr;
_go32_dpmi_seginfo prev_kbd_isr;


int DEBUG = 0;

/*
int kbc_init(int debug){

	disable_irq(KBD_IRQ);
	disable_irq(MOUSE_IRQ);

	DEBUG = debug;
	int mouse_found = 1;

	//ler dados pendentes do KBC
	if(DEBUG) printf("- Flush OBF -\n");
	int data;
	do { data = read_kbc(); } while(data != -1);

	if(DEBUG) printf("- EnableKBD -\n");
	write_kbc_data(EnableKBD);

	if(DEBUG) printf("- MouseEnable -\n");
	write_aux(EnableMouse);

	if(DEBUG) printf("- MouseReset -\n");
	write_aux(MouseReset);
	mili_sleep(500);

	read_kbc();
	read_kbc();

	if(read_kbc() == 0xAA) //BAT sucessful; senao, lanca 0xFC
	{
		if(read_kbc() == 0) //DeviceID
		{
			if(DEBUG) printf("- StreamDisable -\n");
			write_aux(StreamDisable);

			//escrever parametros do rato
			if(DEBUG) printf("- SampleRate -\n");
			write_aux_arg(SampleRate, 100);
			if(DEBUG) printf("- Resolution -\n");
			write_aux_arg(Resolution, 8);
			if(DEBUG) printf("- Scaling -\n");
			write_aux(Scaling1);

			//habilitar rato
			if(DEBUG) printf("- Update Command Byte -\n");
			write_kbc_cmd(ReadCommand);
			mili_sleep(10);
			write_kbc_cmd_arg(WriteCommand, read_kbc() | INT_1 | INT_12 | EN_KBD | EN_MOUSE);

			if(DEBUG) printf("- StreamEnable -\n");
			write_aux(StreamEnable);
		}
	}
	else mouse_found = 0;

	if(DEBUG) printf("- KBDRate -\n");
	write_kbc_data_arg(KBDRate, 0);

	enable_irq(KBD_IRQ);
	enable_irq(MOUSE_IRQ);

	return mouse_found;

}
*/


/** Write 'data' to the command register, returning 0 for OK or -1 on
 * timeout.
 *
 * Uses write_kbc()
 */
int write_kbc_cmd(unsigned data){

	return write_kbc(CMD_REG, data);

}


int write_kbc_cmd_arg(unsigned data, unsigned arg){

	if(write_kbc_cmd(data)) return -1;
	return write_kbc_data(arg);

}


/** Returns 1 if a DOS mouse driver is installed, 0 if not.
 *
 * Needed to know if a DOS mouse driver is installed in order
 *  to reinstall it at program end.
 *
 */
int has_DOS_mouse_ISR(int debug)
{
	return kbc_init(debug);
}


/** Write 'data' to the data register, returning ACK, Error or -1 on timeout.
 *
 * If a Resend reply is received from the KBC, it retries up to 3 times to
 * write the data.
 *
 * Uses write_kbc() and read_kbc()
 */

int write_kbc_data(unsigned data){

	int i, aux;
	for(i = 0; i < 3; i++)
	{
		write_kbc(DATA_REG, data);
		aux = read_kbc();
		if(aux == ACK || aux == Error || aux == -1)
			return aux;

		mili_sleep(1);
	}

	return -1;

}

int write_kbc_data_arg(unsigned data, unsigned arg){

	int resp = write_kbc_data(data);
	if(resp != ACK) return resp;
	return write_kbc_data(arg);

}


/** Send 'cmd' to the mouse, prefacing it with the WriteMouse command
 * to the command register.
 *
 * If a Resend reply is received from the KBC, it retries up to 3 times to
 * write 'cmd', resending the whole sequence.
 *
 * Uses write_kbc_cmd(), write_kbc() and read_kbc()
 */
int write_aux(unsigned cmd)
{
	int i, data;
	for(i = 0; i < 3; i++)
	{
		data = write_kbc_cmd_arg(WriteMouse, cmd);
		if(data == ACK || data == Error || data == -1)
			return data;

		mili_sleep(1);
	}

	return -1;
}

int write_aux_arg(unsigned cmd, unsigned arg)
{
	int resp = write_aux(cmd);
	if(resp != ACK) return resp;
	return write_aux(arg);
}


/** Returns the data read a the data register.
*
*  Waits for OBF on status register up to KBC_TIMEOUT milliseconds,
*  then reads and returns the data read at the data register. Returns
*  -1 on timeout or transmission error.
*/

int read_kbc(void){

	Byte stat, data;
	if(DEBUG) printf("read_kbc: ");
	int timeout = mil_tick + KBC_TIMEOUT;
	while(mil_tick < timeout)
	{
		stat = inportb(STAT_REG);

		//loop until 8042 output buffer full
		if((stat & OBF) != 0)
		{
			data = inportb(DATA_REG);
			//or parity error or receive timeout
			if((stat & (PAR_ERR | TO_ERR)) == 0)
			{
				if(DEBUG) printf("data=%x\n", data);
				return data;
			}
			else
			{
				if(DEBUG) printf("timeout\n");
				return -1;
			}
		}
		mili_sleep(1);
	}
	if(DEBUG) printf("timeout\n");
	return -1;

}


/** Write 'data' at IO address 'adr' , returning -1 on error or timeout.
 *
 * Waits for IBF on status register , than writes data to 'adr',
 * return -1 on timeout.
 */

int write_kbc(unsigned adr, unsigned data){

	Byte stat;
	if(DEBUG) printf("write_kbc: ");

	int timeout = mil_tick + KBC_TIMEOUT;
	while(mil_tick < timeout)
	{
		stat = inportb(STAT_REG);

		//loop until 8042 input buffer empty
		if((stat & IBF) == 0)
		{
			if(DEBUG) printf("add=%x data=%x\n", adr, data);
			outportb(adr, data); //argumentos da função
			return 0;
		}

		mili_sleep(1);
	}
	// terminou o tempo
	if(DEBUG) printf("timeout\n");
	return -1;
}


