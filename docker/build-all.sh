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
ctf/build.sh all build
ctf/build.sh defi1 defi build
ctf/build.sh defi2 defi build
ctf/build.sh defi3 defi build
