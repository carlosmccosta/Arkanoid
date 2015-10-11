#include "CodePage.h"
#include "KBC.h"
#include "Teclado.h"
#include "Rato.h"
#include "RTC.h"
#include "Timer.h"
#include "GraficaVideo.h"
#include "GraficaTexto.h"
#include "Sprite.h"
#include "utypes.h"
#include "Jogo.h"
#include "Music.h"
#include "Menu.h"


int main(int argc, char *argv[])
{
	//>>>>>>>>>>  carregament da codepage  <<<<<<<<<<
	load_char_table(codepage);
	
	
	//>>>>>>>>>>  init kbc  <<<<<<<<<
	Bool mouse_detected = kbc_init(0);
	
	
	//>>>>>>>>>>  init kbd  <<<<<<<<<<
	kbd_init();
	
	
	//>>>>>>>>>>  init mouse  <<<<<<<<<<
	if (mouse_detected == true)
		mouse_init((int) 0);
	
	
	//>>>>>>>>>>  init rtc  <<<<<<<<<<
	rtc_init();
	drawDate();
	drawTime();
	drawCounter();
	
	
	//>>>>>>>>>>  init timer  <<<<<<<<<<
	timer0_init();
	timer_init(TIMER_2, LSBMSB | MODE3);

	
//#################
	menu_start();
//#################		
	
	
	
	//>>>>>>>>>>  restore kbd isr <<<<<<<<<<
	restore_keyboard_isr();
	
	
	//>>>>>>>>>>  restore mouse isr <<<<<<<<<<
	if (mouse_detected == true)
		restore_mouse_isr();
	
	
	//>>>>>>>>>>  restore rtc isr <<<<<<<<<<
	restore_rtc_isr();
	
	//>>>>>>>>>>  init timer isr <<<<<<<<<<
	restore_timer0();
	
	
	return 0;
}
