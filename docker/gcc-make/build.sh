#! /bin/sh

set -e
cd $(dirname $0)

docker build --tag alpine-gcc --label challenge_richelieu .