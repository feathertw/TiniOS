TOOLCHAIN=nds32le-linux
CC= $(TOOLCHAIN)-gcc
AS= $(TOOLCHAIN)-as
LD= $(TOOLCHAIN)-ld
OBJCOPY= $(TOOLCHAIN)-objcopy
OBJDUMP= $(TOOLCHAIN)-objdump
READELF= $(TOOLCHAIN)-readelf
GDB= $(TOOLCHAIN)-gdb

TRANSLATE= python opr/opcode_translate.py

FILE_LIST= elf/main.list
FILE_BIN=  elf/main.bin
FILE_ELF=  elf/main.elf
FILE_RELF= elf/main.relf

SRC=
SRC+= obj/boot.o
SRC+= obj/mput.o
SRC+= obj/mget.o
SRC+= obj/math.o
SRC+= obj/qsort.o
SRC+= obj/gcd.o
SRC+= obj/bcd.o
SRC+= obj/task.o
SRC+= obj/main.o
SRC+= obj/context_switch.o
SRC+= obj/syscalls.o
SRC+= obj/mlib.o

INC=
INC+= inc/main.h
INC+= inc/mlib.h
INC+= inc/mtype.h
INC+= inc/task.h

CFLAGS = -mno-16bit -O2 -S -nostartfiles -nostdlib -I inc
ASFLAGS= -mno-16bit
LDFLAGS= -T src/main.ld

all: $(FILE_BIN) $(FILE_LIST) $(FILE_RELF)

$(FILE_RELF): $(FILE_ELF)
	$(READELF) $^ -s > $@

$(FILE_BIN): $(FILE_ELF)
	$(OBJCOPY) -Obinary $^ $@

$(FILE_LIST): $(FILE_ELF)
	$(OBJDUMP) -D $^ > $@

$(FILE_ELF): $(SRC)
	$(LD) $^ $(LDFLAGS) -o $@

obj/%.o: src/trans_op/_%.s
	$(AS) $< $(ASFLAGS) -o $@

src/trans_op/_%.s: src/trans_as/%.s
	$(TRANSLATE) $< $@



src/trans_op/_%.s: src/%.s
	$(TRANSLATE) $< $@
src/trans_op/_%.s: src/lib/%.s
	$(TRANSLATE) $< $@

src/trans_as/%.s: src/%.c $(INC)
	$(CC) $< $(CFLAGS) -o $@
src/trans_as/%.s: src/lib/%.c $(INC)
	$(CC) $< $(CFLAGS) -o $@
src/trans_as/%.s: src/task/%.c $(INC)
	$(CC) $< $(CFLAGS) -o $@

again: clean all

clean:
	rm -rf elf/*
	rm -rf obj/*
	rm -rf src/trans_op/*
	rm -rf src/trans_as/*

.PHONY: all clean again

.PRECIOUS: src/trans_as/%.s src/trans_op/_%.s obj/%.o
