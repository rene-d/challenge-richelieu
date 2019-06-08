#! /bin/sh

set -e
cd $(dirname $0)

docker build --tag alpine-gcc-make --label challenge_richelieu .