#! /usr/bin/env bash

# construit une image Docker qui ressemble aux machines des défis
# mais avec tous les outils utilisés pour le challenge

set -e
cd $(dirname $0)
if [[ $1 == --quiet ]]; then quiet=--quiet; shift; else quiet=; fi

distro=stretch
if [[ $1 == stretch ]]; then shift; fi
if [[ $1 == buster ]]; then distro=buster; shift; fi

docker build ${quiet} --label challenge_richelieu \
    --build-arg DISTRO=${distro} \
    -t dgse:hacking -t dgse:hacking-${distro} -t dgse .

docker image prune --force
docker images | grep "^.none" | awk '{print $3}' | xargs docker rmi

if [[ $1 == run ]]
then
    DGSE=$(git rev-parse --show-toplevel)
    docker run --rm -ti --name dgse --hostname dgse -v ${DGSE}:/dgse --cap-add=SYS_PTRACE dgse
fi
