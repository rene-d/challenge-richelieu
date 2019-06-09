#!/usr/bin/env bash
set -Eeuo pipefail

export LANG=fr_FR.UTF-8
export LC_CTYPE=C.UTF-8

[ $(tty) != "/dev/pts/0" ] && echo -e "I am on tty \033[01;33m$(tty)\033[0m"

cd /dgse
exec "$@"
