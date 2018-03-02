# définition de quelques variables
MEMSIZE := 0x40
TARGET  := prem
CC      := sdcc
AS	:= sdasz80
CFLAGS  := 
LFLAGS  := -Wl-u
MFLAGS  := -mz80 --code-loc 0x0006 --data-loc 0x0000 --vc --verbose 

# Tout construire c'est construire prem.bin et prem_padded.bin
all: ${TARGET}.bin ${TARGET}_padded.bin

# Assemblage du crt0
crt0.rel: crt0.s
	$(AS) -plosgffw crt0.rel crt0.s

# Compilation de prem.c et édition de liens
${TARGET}.ihx: ${TARGET}.c crt0.rel
	$(CC) $(MFLAGS) $(LFLAGS) --no-std-crt0 crt0.rel ${TARGET}.c

# Conversion de l'Intel Hex en binaire
${TARGET}.bin: ${TARGET}.ihx
	makebin -p < ${TARGET}.ihx > ${TARGET}.bin

${TARGET}_padded.bin: ${TARGET}.ihx
	sdobjcopy -Iihex -Obinary --gap-fill 0x00 --pad-to \
	$(MEMSIZE) ${TARGET}.ihx ${TARGET}_padded.bin

# Désassemblage à l'écran
disasm: ${TARGET}.bin
	z80dasm -g 0x0 -l ${TARGET}.bin

# Affichage du code machine
dump: ${TARGET}.bin
	xxd -c 16 -i ${TARGET}.bin

# Affichage du code machine à la taille de la mémoire
dumppad: ${TARGET}_padded.bin
	xxd -c 16 -i ${TARGET}_padded.bin

# Affacement des fichiers, nettoyage
clean:
	rm -f *.cdb *.rel *.hex *.ihx *.lst *.map *.o *.rst \
	*.sym *.lnk *.lib *.bin *.mem *.lk *.noi *.asm
