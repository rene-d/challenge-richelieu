#! /bin/bash

# construit une image Docker qui ressemble aux machines des défis
# mais avec tous les outils utilisés pour le challenge

set -e
cd $(dirname $0)

docker build -t dgse:stretch -t dgse --label challenge_richelieu .

docker image prune --force
docker images | grep "^.none" | awk '{print $3}' | xargs docker rmi

# docker run --rm -ti --name dgse --hostname dgse -v $HOME/dgse:/dgse --cap-add=SYS_PTRACE dgse
