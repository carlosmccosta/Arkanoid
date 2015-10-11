CC = gcc
AS = nasm
CFLAGS = -Wall
ASFLAGS = -t -g -f coff
OBJS_CC = Altifalante.o Bloco.o BlocoDB.o Bola.o CodePage.o GQueue.o GraficaTexto.o GraficaVideo.o Interrupcoes.o Jogador.o Jogo.o KBC.o Mapa.o MapasDB.o Menu.o Music.o MusicDB.o Nave.o Queue.o Rato.o RecordsDB.o RTC.o Songs.o Sprite.o SpriteDB.o Teclado.o Timer.o Vector.o kbc_init.o
OBJS_AS = kbd_isr.o mouse_isr.o mouse_isr_gqueue.o timer_isr.o rtc_isr.o
EXTRAH = utypes.h 
OUTFILE = Arkanoid.exe

all: $(OUTFILE)

$(OUTFILE): main.c $(EXTRAH) $(OBJS_CC) $(OBJS_AS)
	@echo Linking files ...
	@$(CC) $(CFLAGS) main.c $(EXTRAH) $(OBJS_CC) $(OBJS_AS) -o $(OUTFILE)
	@echo Program ready to execute

%.o: %.c %.h
	@echo Compiling $< ...
	@$(CC) $(CFLAGS) -c $<
	@echo done

%.o: %.asm
	@echo Assembling $< ...
	@$(AS) $(ASFLAGS) $<
	@echo done

clean:
	@echo Cleaning up ...
	@rm -f *.o $(OUTFILE)
	@echo done

rebuild: clean all
