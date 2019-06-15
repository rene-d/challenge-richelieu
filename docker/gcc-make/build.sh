#! /usr/bin/env bash

set -e
cd $(dirname $0)
if [[ $1 == --quiet ]]; then quiet=--quiet; shift; else quiet=; fi

docker build ${quiet} --label challenge_richelieu --tag alpine-gcc-make .
