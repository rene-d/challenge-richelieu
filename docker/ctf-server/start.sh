#! /usr/bin/env bash

set -e
cd $(dirname $0)

m()
{
    echo -e "\033[32m$@\033[0m"
}


m "nettoyage ancienne instance"
./stop.sh

# construit l'image du server ssh
if [[ $1 = "all" ]]
then
    shift
    image=dgse:ctf-server-all
    more_ports="-p 8000:8000"
else
    if [[ $1 =~ defi[[:digit:]] ]]
    then
        user=$1
        shift 1
    else
        user=defi1
    fi
    image=dgse:ctf-server-${user##user}
    more_ports=""
fi

m "démarrage serveur SSH ${image}"
docker run --name ctf_server -d --rm -p 2222:22 ${more_ports} -v /var/run/docker.sock:/var/run/docker.sock ${image}

if [[ "$1" == "sh" ]]; then
    m "console sur serveur"
    docker exec -ti ctf_server sh
fi
