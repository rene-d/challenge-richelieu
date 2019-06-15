#! /usr/bin/env bash

cd $(dirname $0)

m()
{
    echo -e "\033[1;34m$@\033[0m"
}
 
m "nettoyage"
docker container prune --force
docker image prune --force
docker images | grep "^.none" | awk '{print $3}' | xargs docker rmi

m "alpine gcc make"
gcc-make/build.sh --quiet

m "outils"
hacking/build.sh --quiet

m "ctf"
ctf/build.sh --quiet

m "ctf-serveur"
ctf-server/build.sh --quiet all
ctf-server/build.sh --quiet defi1 defi
ctf-server/build.sh --quiet defi2 defi
ctf-server/build.sh --quiet defi3 defi
