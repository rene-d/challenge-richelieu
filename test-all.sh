#! /usr/bin/env bash

cd $(dirname $0)

m()
{
    printf "\n\033[1;33m====== %s ======\033[0m\n\n" "$@"
}

m "images docker"
./docker/build-all.sh

m "étapes 1-8"
./challenge1/test-exploit.sh

m "étape 9"
./challenge2/test-exploit.sh

m "étapes 10"
./defi1/test-exploit.sh

m "étapes 11"
./defi2/test-exploit.sh

m "étapes 12"
./defi3/test-exploit.sh
