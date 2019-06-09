#! /bin/bash

cd $(dirname $0)

m()
{
    echo -e "\033[1;34m$@\033[0m"
}

m "alpine gcc"
gcc-make/build.sh --quiet

m "outils"
hacking/build.sh --quiet

m "ctf"
ctf/build.sh --quiet

m "ctf-serveur"
ctf-server/start.sh --quiet all norun
ctf-server/start.sh --quiet defi1 defi norun
ctf-server/start.sh --quiet defi2 defi norun
ctf-server/start.sh --quiet defi3 defi norun
