#! /bin/bash

set -e

docker build -t dgse:buster .
docker run --rm -ti --name dgse_buster --hostname dgse -v $HOME/dgse:/dgse --cap-add=SYS_PTRACE dgse:buster

docker images | grep "^.none" | awk '{print $3}' | xargs docker rmi
