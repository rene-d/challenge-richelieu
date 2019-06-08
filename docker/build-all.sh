#! /bin/bash

m()
{
    echo -e "\033[32m$@\033[0m"
}

m "alpine gcc"
gcc-make/build.sh

m "outils"
stretch/build.sh

m "ctf"
ctf/build.sh

m "ctf-serveur"
ctf-server/start.sh all build
ctf-server/start.sh defi1 defi build
ctf-server/start.sh defi2 defi build
ctf-server/start.sh defi3 defi build
