# See genscripts.sh and ../scripttempl/elf.sc for the meaning of these.
SCRIPT_NAME=elf
ELFSIZE=64
TEMPLATE_NAME=elf32
OUTPUT_FORMAT="elf64-ia64-aix-little"
ARCH=ia64
MACHINE=
MAXPAGESIZE=0x1000
TEXT_START_ADDR="0x100000000"
DATA_ADDR="0x200000000 + (. & (${MAXPAGESIZE} - 1))"
GENERATE_SHLIB_SCRIPT=yes
NOP=0x00300000010070000002000001000400  # a bundle full of nops
#OTHER_GOT_SYMBOLS='. = ALIGN (8); PROVIDE (__gp = . + 0x200000);'
OTHER_GOT_SECTIONS='.IA_64.pltoff : { *(.IA_64.pltoff) }'
OTHER_PLT_RELOC_SECTIONS='.rela.IA_64.pltoff : { *(.rela.IA_64.pltoff) }'
OTHER_READONLY_SECTIONS='.opd : { *(.opd) }'
#LIB_PATH=/usr/lib/ia64l64:/usr/lib:/usr/local/lib
