#! /bin/bash

docker build -t dgse:stretch . && docker run --rm -ti -v $HOME/dgse:/dgse --cap-add=SYS_PTRACE -h dgse dgse:stretch

