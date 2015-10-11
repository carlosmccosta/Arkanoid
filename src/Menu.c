#include "Menu.h"


void print_rules() {
	fillScreen(0);
	//system("cls");

	drawFrame(" >>>>> INSTRUCOES <<<<< ", 0x0A, 0, 0, 80, 25);
	printStringAt("  Para movimentar a nave utilize as setas do teclado.", 14, 9, 0x0A);
	printStringAt("Tente destruir todos os blocos no menor espaco de tempo.", 14, 10, 0x0A);
	printStringAt("Se deixar cair a bola mais de 5 vezes perde o jogo.", 14, 11, 0x0A);
	printStringAt("       Os mapas sao gerados aleatoriamente.", 14, 12, 0x0A);
	printStringAt(" Caso queira experimentar outro mapa, reinicie o jogo.", 14, 13, 0x0A);
	printStringAt("ESC - Voltar", 2, 23, 0x04);
}

void modo_mapa() {
	fillScreen(0);
	//system("cls");

	drawFrame(" >>>>> Modo de carregamento do mapa <<<<< ", 0x0A, 0, 0, 80, 25);
	printStringAt("  Modo de carregamento do mapa do jogo pode ser:", 14, 9, 0x0A);
	printStringAt("1 - Normal    -> o mapa e um rectangulo de blocos;", 14, 15, 0x0A);
	printStringAt("2 - Aleatorio -> o mapa e desenhado aleatoriamente;;", 14, 16, 0x0A);
	printStringAt("1 - Mapa normal", 4, 20, 0x0A);
	printStringAt("2 - Mapa gerado aleatoriamente", 4, 21, 0x0A);
	printStringAt("ESC - Voltar", 2, 23, 0x04);
}

void print_menu() {
	fillScreen(0);
	//system("cls");

	drawFrame(" >>>>>  LCOM 2010 / 2011 -- T5G4 -- Arkanoid  <<<<< ", 0x09, 0, 0, 80, 25);

	printStringAt("    {}      {*****}   {    {     {}      #   #   {==}   #####  {****}  ", 4, 6, 0x02);
	printStringAt("   {  }     #      }  #  {      {  }     ##  #  {    }    #    #     } ", 4, 7, 0x02);
	printStringAt("  { == }    #*****}   #{       { == }    # # #  #    #    #    #     # ", 4, 8, 0x02);
	printStringAt(" {      }   #     }   # {     {      }   #  ##  {    }    #    #     } ", 4, 9, 0x02);
	printStringAt("{        }  #      }  #   {  {        }  #   #   {==}   #####  {****}  ", 4, 10,0x02);


	printStringAt("                                                 Desenvolvido por:     ", 4, 15,0x02);
	printStringAt("                                              Carlos Costa - ei09097   ", 4, 16,0x02);
	printStringAt("                                            Wilson Pimentel - ei09052  ", 4, 17,0x02);

	printStringAt("1 - Jogar", 4, 19, 0x0A);
	printStringAt("2 - Instrucoes", 4, 20, 0x0A);
	printStringAt("3 - Mapas", 4, 21, 0x0A);
	printStringAt("ESC - Sair", 4, 23, 0x04);
}

void menu_start() {
	unsigned char SC;
	Bool exit = false;
	int modo_carregamento_mapas = 0;

	fillScreen(0);
	print_menu();
	play_array_notes(main_song);
	play_array_notes(main_song);

	do {
		//while (queueEmpty(&keys_queue) == false) {}
		SC = queueGet(&keys_queue);

		switch (SC) {
			case SC_1: {
				fillScreen(0);
				startJogo(modo_carregamento_mapas);
				fillScreen(0);
				mili_sleep(10);
				print_menu();
				exit = true;
				break;
			}

			case SC_2: {
				fillScreen(0);
				print_rules();
				play_array_notes(main_song);
				while (SC != SC_ESC) { SC = queueGet(&keys_queue); }

				exit = false;
				fillScreen(0);
				print_menu();
				break;
			}

			case SC_3: {
				fillScreen(0);
				modo_mapa();
				play_array_notes(main_song);
				while ((SC != SC_ESC) && (SC != SC_1) && (SC != SC_2)) { SC = queueGet(&keys_queue); }
				if (SC == SC_1)
					modo_carregamento_mapas = 0;
				else if (SC == SC_2)
					modo_carregamento_mapas = 1;

				print_menu();
				exit = false;
				break;
			}

			case SC_ESC: {
				exit = true;
				break;
			}
		}
	}

	while (exit != true);

	fillScreen(0);
	//system("cls");
}

