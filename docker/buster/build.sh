#! /bin/bash

docker build -t dgse . && docker run --rm -ti -v $HOME/dgse:/dgse --cap-add=SYS_PTRACE -h dgse dgse

docker images | grep "^.none" | awk '{print $3}' | xargs docker rmi
