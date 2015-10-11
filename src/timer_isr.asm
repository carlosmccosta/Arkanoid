CPU 686
BITS 32

%define EOI 20h		; define EOI como valendo 0x20
global _mil_tick		; declara nome_var como acessível a módulos escritos em C
global _sec_tick		; declara nome_var como acessível a módulos escritos em C
global _t0_isr		; o handler também deve ser global, para ser instalado

section .data		; .data é a zona de dados inicializados
					; declara variável nome_var com 4 bytes (dd) e inicializa-a com 0
_mil_tick dd 0;
_sec_tick dd 0;
contador dd 1000;

section .text		; .text é a zona de código
_t0_isr:			; deve ser global para ser acedida em módulos escritos em C
	pusha			; todos os registos utilizados na rotina
	inc dword[_mil_tick]
	dec dword[contador]
	jne fim
	inc dword[_sec_tick]
	mov dword[contador],1000
fim:
	mov al, EOI		; sinaliza EOI para o PIC-1
	out 20h, al
	popa			; todos os registos guardados
	iretd
END ; fim de código fonte assembly