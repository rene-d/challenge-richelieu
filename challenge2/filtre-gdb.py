#! /usr/bin/env python3

import re
import sys

if len(sys.argv) <= 1:
    txt = "output.txt"
else:
    txt = sys.argv[1]

d = []
n = 0
next_a = 0
for s in open(txt):
    s = s.strip()

    # on ne garde que les lignes commençant par ""=> 0x00" i.e. les lignes avec instruction assembleur
    if not re.match(r"^=> 0x00", s):
        continue

    m = re.match(r"=> (0x[0-9a-f]+):\t(.+)\t(.*)$", s)

    a, b, i = m.groups()

    # calcule la longueur max du bytecode, pour aligner l'assembleur
    if n < len(b):
        n = len(b)

    # marque les sauts en rajoutant une ligne vide
    if next_a != int(a, base=0):
        d.append(('', '', ''))

    d.append((a, b, i))
    next_a = int(a, base=0) + (1 + len(b)) // 3

# affiche le résultat
for a, b, i in d:
    if a == '':
        print()
    else:
        print(("{} {:" + str(n) + "} {}").format(a, b, i))
