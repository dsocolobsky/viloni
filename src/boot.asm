extern kmain
extern GDT_DESC

; Multiboot header
MBALIGN     equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MBALIGN | MEMINFO
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC+FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16386 ; 16KiB
stack_top:

section .text
bits 32
global _start
_start:
    cli
    cld

    ; We are now in 32bit protected mode, PE is enabled
    ; eax has 0x1BADB002, ebx has phy address of the Multiboot
    ; information data structure

    ; Set up stack
    mov esp, stack_top


    ; Clear screen
    %define VGABUF 0xB8000
    ; Clear screen
	mov ecx, 2000 ; 80 * 25 characters in the buffer
	jmp .cls_end
.cls:
	dec ecx
	mov word [VGABUF + ecx * 2], 0x0F20
.cls_end:
	cmp ecx, 0
	jne .cls
    
    ; load GDT
    lgdt [GDT_DESC]


    ; load Paging
    ;call kmain

    ; Ciclar infinitamente
    cli
    jmp $
.end: