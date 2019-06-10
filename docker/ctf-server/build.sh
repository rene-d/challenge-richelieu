#! /bin/bash

set -e
cd $(dirname $0)
if [[ $1 == --quiet ]]; then quiet=--quiet; shift; else quiet=; fi

m()
{
    echo -e "\033[32m$@\033[0m"
}

# compile shell.c avec gcc dockerisé
m "compilation /bin/ctfsh"
../gcc-make/build.sh ${quiet}
docker run -ti --rm -v $PWD:/work -w /work alpine-gcc-make make

# construit l'image du server ssh
if [[ $1 = "all" ]]
then
    shift

    image=dgse:ctf-server-all
    more_ports="-p 8080:80"

    if [ ! -f web.tar.gz ]
    then
        tar -C ../../web/ -czvf web.tar .
    fi

    m "création image ${image}"
    docker build ${quiet} --label challenge_richelieu --tag ${image} -f Dockerfile-all .
else
    if [[ $1 =~ defi[[:digit:]] ]]
    then
        user=$1
        password=${2:-defi}
        shift 2
    else
        user=defi1
        password=defi
    fi

    image=dgse:ctf-server-${user##user}
    more_ports=""

    m "création image ${image} pour user=${user} password=${password}"
    docker build ${quiet} --label challenge_richelieu \
        --build-arg "USER=${user}" \
        --build-arg "PASSWORD=${password}" \
        --tag ${image} .
fi
