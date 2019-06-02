#! /bin/bash

set -e

docker build -t dgse:stretch -t dgse .
docker run --rm -ti --name dgse --hostname dgse -v $HOME/dgse:/dgse --cap-add=SYS_PTRACE dgse

docker images | grep "^.none" | awk '{print $3}' | xargs docker rmi
