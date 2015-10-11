CPU 686
BITS 32

%define DATA_REG 0x60
%define EOI 0x20
%define PIC1_CMD 0x20
%define PIC2_CMD 0xA0

global _mouse_isr
global _mouse_isr_end
global _mouse_byte1
global _mouse_byte2
global _mouse_byte3
global _pack_completo


section .data
_mouse_byte1 db 0
_mouse_byte2 db 0
_mouse_byte3 db 0
_pack_completo db 0

next_byte dd 1

section .text

_mouse_isr:
	push eax
	push ecx
	
	xor eax, eax
	in al, DATA_REG
	
	mov ecx, dword[next_byte]
	
	cmp ecx, 3
	je byte3
	cmp ecx, 2
	je byte2
	
byte1:
	mov byte[_mouse_byte1], al
	mov byte[_pack_completo], 0
	mov ecx, 2
	jmp fim

byte2:
	mov byte[_mouse_byte2], al
	mov byte[_pack_completo], 0
	mov ecx, 3
	jmp fim
	
byte3:
	mov byte[_mouse_byte3], al
	mov byte[_pack_completo], 1
	mov ecx, 1

fim:
	mov byte[next_byte], al
	mov al, EOI
	out PIC1_CMD, al
	out PIC2_CMD, al
	pop ecx
	pop eax
	iretd
_mouse_isr_end:
END