/**\file RTC.c
 * \brief Módulo usado para a leitura dos dados do relógio, para os logs/records do jogo
 *
 * PROJECTO: Projecto - Arkanoid \n
 * FICHEIRO: RTC.c \n
 * DESCRIÇÃO: Módulo usado para a leitura dos dados do relógio, para os logs/records do jogo \n
 *
 * TURMA : COMP_155 \n
 * AUTORES:
 * - Carlos Miguel Correia da Costa
 * - Wilson Beto Amaral Pimentel
 */
#include "RTC.h"

_go32_dpmi_seginfo prev_rtc_isr;

RTC_TIME prev_time;
RTC_TIME time_rtc;
RTC_TIME inicial_time;
RTC_TIME counter = {0,0,0};
RTC_DATE date;


void rtc_isr(void) {
	outportb(RTC_ADDR_REG, RTC_STAT_C);
	Byte cause = read_rtc(RTC_STAT_C);
	
	if(cause & RTC_PF) { // periodic interrupt
		drawTime();
		//updateCounter();
		drawCounter();
	}
		
	outportb(PIC1_CMD, EOI);
	outportb(PIC2_CMD, EOI);
}

void lock_rtc_isr() { _go32_dpmi_lock_code(get_time, (unsigned long)(lock_rtc_isr - rtc_isr)); }

void drawDate() {
	rtc_read_date(&date);
	//desenho da data no frame do jogo
	if (date.day < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", DATE_X_POS_FRAME, DATE_Y_POS_FRAME, NUMEBR_BACKGROUD_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)date.day, DATE_X_POS_FRAME, DATE_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	drawCharAt('/', DATE_X_POS_FRAME + OFFSET_NUMBERS, DATE_Y_POS_FRAME, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	if (date.month < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", DATE_X_POS_FRAME + 2 * OFFSET_NUMBERS, DATE_Y_POS_FRAME, NUMEBR_BACKGROUD_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)date.month, DATE_X_POS_FRAME + 2 * OFFSET_NUMBERS, DATE_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	drawCharAt('/', DATE_X_POS_FRAME + 3 * OFFSET_NUMBERS, DATE_Y_POS_FRAME, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	if (date.year < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", DATE_X_POS_FRAME + 4 * OFFSET_NUMBERS, DATE_Y_POS_FRAME, NUMEBR_BACKGROUD_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)date.year, DATE_X_POS_FRAME + 4 * OFFSET_NUMBERS, DATE_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
}

void drawTime() {
	prev_time = time_rtc;
	rtc_read_time(&time_rtc);
	
	//desenho da hora no frame do jogo
	if (time_rtc.hour < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", TIME_X_POS_FRAME, TIME_Y_POS_FRAME, NUMEBR_BACKGROUD_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)time_rtc.hour, TIME_X_POS_FRAME, TIME_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	drawCharAt(':', TIME_X_POS_FRAME + OFFSET_NUMBERS, TIME_Y_POS_FRAME, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	if (time_rtc.min < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", TIME_X_POS_FRAME + 2 * OFFSET_NUMBERS, TIME_Y_POS_FRAME, NUMEBR_BACKGROUD_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)time_rtc.min, TIME_X_POS_FRAME + 2 * OFFSET_NUMBERS, TIME_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	drawCharAt(':', TIME_X_POS_FRAME + 3 * OFFSET_NUMBERS, TIME_Y_POS_FRAME, CHAR_FOREGROUND_COLOR, CHAR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	if (time_rtc.sec < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", TIME_X_POS_FRAME + 4 * OFFSET_NUMBERS, TIME_Y_POS_FRAME, NUMEBR_BACKGROUD_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)time_rtc.sec, TIME_X_POS_FRAME + 4 * OFFSET_NUMBERS, TIME_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, NUMEBR_BACKGROUD_COLOR, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);

}

void updateCounter() {
	++counter.sec;
	
	if(counter.sec == 60) {
		counter.sec = 0;
		++counter.min;
	}
	
	if(counter.min == 60) {
		counter.min = 0;
		++counter.hour;
	}
}

void startCounterVsTime() {
	rtc_read_time(&inicial_time);
}

void updateCounterVsTime() {
	if (prev_time.sec != time_rtc.sec)
		updateCounter();

/*
	counter.hour = time_rtc.hour - inicial_time.hour;
	counter.min = time_rtc.min - inicial_time.min;
	counter.sec = time_rtc.sec - inicial_time.sec;
*/
}

void drawCounter() {
	//desenho da hora no frame do jogo
	if (counter.hour < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", COUNTER_X_POS_FRAME, COUNTER_Y_POS_FRAME, COUNTER_BACKGROUND, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)counter.hour, COUNTER_X_POS_FRAME, COUNTER_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	drawCharAt(':', COUNTER_X_POS_FRAME + OFFSET_NUMBERS, COUNTER_Y_POS_FRAME, CHAR_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	if (counter.min < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", COUNTER_X_POS_FRAME + 2 * OFFSET_NUMBERS, COUNTER_Y_POS_FRAME, COUNTER_BACKGROUND, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)counter.min, COUNTER_X_POS_FRAME + 2 * OFFSET_NUMBERS, COUNTER_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	drawCharAt(':', COUNTER_X_POS_FRAME + 3 * OFFSET_NUMBERS, COUNTER_Y_POS_FRAME, CHAR_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	
	if (counter.sec < (Byte)10) //limpa os numeros anteriores
		drawStringAt("00", COUNTER_X_POS_FRAME + 4 * OFFSET_NUMBERS, COUNTER_Y_POS_FRAME, COUNTER_BACKGROUND, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
	drawIntAt((int)counter.sec, COUNTER_X_POS_FRAME + 4 * OFFSET_NUMBERS, COUNTER_Y_POS_FRAME, NUMBER_FOREGROUND_COLOR, COUNTER_BACKGROUND, CHAR_SCALE, VIDEO_BASE_ADDRESS, codepage);
}



void rtc_init() {
	mask_pic(RTC_IRQ);
	
	lock_rtc_isr();
	lock_rtc_valid();
	lock_read_rtc();
	lock_write_rtc();
	lock_bcd2dec();
	
	set_isr_c_wrapper(RTC_IRQ, rtc_isr, &prev_rtc_isr);
	
	rtc_int_enable();
	rtc_int_enable_periodic();
	
	unmask_pic(RTC_IRQ);
}

void restore_rtc_isr() {
	mask_pic(RTC_IRQ);
	restore_isr_c_wrapper(RTC_IRQ, &prev_rtc_isr);
}


void bcd2decHandler(){}


Byte bcd2dec(Byte i)
{
	return (i & 0x0F) + 10 * ((i >> 4) & 0x0F);
}

void lock_bcd2dec() { _go32_dpmi_lock_code(bcd2dec, (unsigned long)(lock_bcd2dec - bcd2decHandler)); }



Byte dec2bcd(Byte i)
{
	return (i % 10) + (((i / 10) % 10) << 4);
}


void rtc_int_enable()
{
	//programar RTC para gerar periodic ints a um rate de 1024KHz
	write_rtc(RTC_STAT_A, (read_rtc(RTC_STAT_A) & 0xF0) | 0x06);
	unmask_pic(RTC_IRQ);
}


void rtc_int_enable_periodic()
{
	write_rtc(RTC_STAT_B, (read_rtc(RTC_STAT_B) & 0x8F) | RTC_PIE);
	read_rtc(RTC_STAT_C);
}


void rtc_int_disable()
{
	mask_pic(RTC_IRQ);
	write_rtc(RTC_STAT_B, read_rtc(RTC_STAT_B) & ~(RTC_PIE | RTC_AIE | RTC_UIE));
}


void rtc_valid()
{
	int old_pic1 = get_pic1(), old_pic2 = get_pic2();
	set_pic_var(0xFF, 0xFF);

	outportb(RTC_ADDR_REG, RTC_STAT_A); // read STAT_A
	
	// wait if Update In Progress (UIP)
	while (inportb(RTC_DATA_REG) & RTC_UIP)
	; // data is invalid
	
	set_pic_var(old_pic1, old_pic2);
}

void lock_rtc_valid() { _go32_dpmi_lock_code(rtc_valid, (unsigned long)(lock_rtc_valid - rtc_valid)); }


void read_rtcHandler() {}


Byte read_rtc(Byte add)
{
	int old_pic1 = get_pic1(), old_pic2 = get_pic2();
	set_pic_var(0xFF, 0xFF);

	outportb(RTC_ADDR_REG, add);
	Byte val = inportb(RTC_DATA_REG);

	set_pic_var(old_pic1, old_pic2);
	return val;
}

void lock_read_rtc() { _go32_dpmi_lock_code(read_rtc, (unsigned long)(lock_read_rtc - read_rtcHandler)); }



Byte read_rtcv(Byte add)
{
	rtc_valid();
	return read_rtc(add);
}


void write_rtcHandler() {}


void write_rtc(Byte add, Byte value)
{
	int old_pic1 = get_pic1(), old_pic2 = get_pic2();
	set_pic_var(0xFF, 0xFF);

	outportb(RTC_ADDR_REG, add);
	outportb(RTC_DATA_REG, value);

	set_pic_var(old_pic1, old_pic2);
}

void lock_write_rtc() { _go32_dpmi_lock_code(write_rtc, (unsigned long)(lock_write_rtc - write_rtcHandler)); }


void write_rtcv(Byte add, Byte value)
{
	rtc_valid();
	write_rtc(add, value);
}


void rtc_read_time(RTC_TIME* rt)
{
	rt->hour = bcd2dec(read_rtcv(HOUR));
	rt->min = bcd2dec(read_rtcv(MIN));
	rt->sec = bcd2dec(read_rtcv(SEC));
}


void rtc_read_date(RTC_DATE* rd)
{
	rd->year = bcd2dec(read_rtcv(YEAR));
	rd->month = bcd2dec(read_rtcv(MONTH));
	rd->day = bcd2dec(read_rtcv(MONTH_DAY));
}


void rtc_read_alarm(RTC_TIME* rt)
{
	rt->hour = bcd2dec(read_rtcv(HOUR_ALARM));
	rt->min = bcd2dec(read_rtcv(MIN_ALARM));
	rt->sec = bcd2dec(read_rtcv(SEC_ALARM));
}


void rtc_write_alarm(RTC_TIME* rt)
{
	write_rtcv(HOUR_ALARM, dec2bcd(rt->hour));
	write_rtcv(MIN_ALARM, dec2bcd(rt->min));
	write_rtcv(SEC_ALARM, dec2bcd(rt->sec));
}
