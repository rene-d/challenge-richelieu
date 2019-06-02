#! /bin/sh

# stop on error
set -e

# nécessite une deuxième console:
#   docker exec -ti dgse bash

prog=./prog.bin
prog=./defi

clear > /dev/pts/1
make
ltrace -o trace ${prog} < response && villoc trace out.html

gdb -q -nx -ex "source /opt/gef-master/gef.py" -ex "file ${prog}" -ex "b choix_menu" -ex "run < response > /dev/pts/1"
