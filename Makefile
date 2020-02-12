ISO    := build/viloni.iso
KERNEL := build/viloni.elf

AS := nasm
CC := gcc

ASFLAGS := -f elf64 -F dwarf -g -w+all -Werror

CFLAGS := -ffreestanding -mno-red-zone -Iinclude -m64 -std=gnu11 -fno-pie -no-pie -fno-zero-initialized-in-bss -fno-stack-protector
CFLAGS := -Wall -O0 -g -ggdb
CFLAGS += -mno-sse -mno-mmx -mno-sse2 -mno-sse3 -mno-ssse3 -mno-sse4 -mno-sse4.1 -mno-sse4.2 -mno-avx -mno-sse4a

KERNEL_OBJ := src/boot.asm.o src/kernel.asm.o src/gdt.c.o

.PHONY: all clean bochs qemu run

all: clean $(ISO)

run: clean $(ISO) bochs

clean:
	rm -f build/*
	rm -f src/*.o
	rm -f src/*.d

bochs:
	@bochs -f bochsrc -q

qemu:
	qemu-system-x86_64 -net none -smp sockets=1,cores=4,threads=1 -serial stdio -cdrom $(ISO)

build/:
	@mkdir build

iso/boot/viloni.elf: $(KERNEL)
	@echo 'copying iso'
	cp $< $@

$(ISO): build/ iso/boot/viloni.elf
	@echo 'Creating ISO'
	grub-mkrescue -o $@ iso 2> /dev/null

$(KERNEL): $(KERNEL_OBJ)
	@echo 'Linking kernel'
	$(CC) -T scripts/linker.ld -o $@ $(KERNEL_OBJ) $(LDFLAGS) -n -nostdlib -lgcc -fno-pie -no-pie
	objcopy --only-keep-debug $(KERNEL) build/viloni.sym
	objcopy --strip-debug $(KERNEL)
	@grub-file --is-x86-multiboot $@

src/%.asm.o: src/%.asm
	@echo 'Assembling'
	$(AS) $(ASFLAGS) -MD $(addsuffix .d,$<) $< -o $@

src/%.c.o: src/%.c
	@echo 'Compiling'
	@$(CC) -c $< -MMD $(CFLAGS) -o $@
