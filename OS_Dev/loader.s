global loader   ;entry symbol used by elf

MAGIC_NUMBER equ 0x1BADB002 ; define onstants
FLAGS equ 0x0
CHECKSUM equ -MAGIC_NUMBER

section .text:  ;start a section of code
align 4 ; 4-byte aligned
	dd MAGIC_NUMBER ;write the values
	dd FLAGS
	dd CHECKSUM

loader:
	mov eax, 0xCAFEBABE ;move value to eax register
.loop:
	jmp .loop  ;jmp to label
