CPU 686
BITS 32

%define    PIC1_CMD 20h
%define    EOI 20h             ; define EOI como valendo 0x20
global     _millis              ; declara nome_var como acessível a módulos escritos em C
global     _t0_isr             ; o handler também deve ser global, para ser instalado

section    .data               ; .data é a zona de dados inicializados
_millis  dd 0                   ; declara variável nome_var com 4 bytes (dd) e inicializa-a com 0

section    .text               ; .text é a zona de código
_t0_isr:                       ; deve ser global para ser acedida em módulos escritos em C
           push  eax           ; todos os registos utilizados na rotina
           inc dword[_millis]   ; instruções da rotina
           mov   al, EOI       ; sinaliza EOI para o PIC-1
           out   PIC1_CMD, al
           pop   eax           ; todos os registos guardados
           iretd
END                            ; fim de código fonte assembly