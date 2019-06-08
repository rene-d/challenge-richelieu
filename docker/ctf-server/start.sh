#! /bin/bash

set -e
cd $(dirname $0)

m()
{
    echo -e "\033[32m$@\033[0m"
}

# compile shell.c avec gcc dockerisé
m "compilation /bin/ctfsh"
../gcc-make/build.sh
docker run -ti --rm -v $PWD:/work -w /work alpine-gcc-make make

# construit l'image du server ssh
if [[ $1 = "all" ]]
then
    shift
    image=dgse:ctf-server-all
    m "création image ${image}"
    docker build --label challenge_richelieu --tag ${image} -f Dockerfile-all .
else
    if [[ $1 =~ defi[[:digit:]] ]]
    then
        user=$1
        password=$2
        shift 2
    else
        user=defi1
        password=defi
    fi
    image=dgse:ctf-server-${user##user}

    m "création image ${image} pour user=${user} password=${password}"
    docker build --label challenge_richelieu \
        --build-arg "USER=${user}" \
        --build-arg "PASSWORD=${password}" \
        --tag ${image} .
fi

if [[ $1 = build ]]
then
    exit
fi

m "nettoyage ancienne instance"
./clean-ctf.sh 0
docker rm --force ctf_server || true

m "démarrage serveur SSH"
docker run --name ctf_server -d --rm -p 2222:22 -v /var/run/docker.sock:/var/run/docker.sock ${image}

if [[ "$1" == "sh" ]]; then
    m "console sur serveur"
    docker exec -ti ctf_server sh
fi
