#! /usr/bin/env bash

if [[ $1 = serv ]]; then
    docker rm --force ctf-server &> /dev/null
    docker run --name ctf-server -d --rm -p 2222:22 -v /var/run/docker.sock:/var/run/docker.sock dgse:ctf-server-all
    exit
fi

if [[ $1 = stop ]]; then
    $(dirname $0)/docker/ctf-server/clean-ctf.sh 0
    docker rm --force ctf-server &> /dev/null
    exit
fi

if [[ $1 ]]; then
    docker run --label defi$1 --hostname AttrapeLeDrapeau --network none --rm -ti --cap-add=SYS_PTRACE dgse:defi$1
    exit
fi

ID=$(
    docker ps -a --format "{{.ID}} {{.Names}}" | while read -r ID NAMES
    do
        if [[ ${NAMES} == "dgse" ]]; then
            echo ${ID}
            break
        fi
    done
)

if [[ ${ID} ]]; then
    echo "Attaching a new terminal to the container"
    docker exec -ti ${ID} bash
else
    echo "Starting the container"
    DGSE=$(cd $(dirname $0); pwd)
    docker run --name dgse --hostname dgse --rm -ti -v "${DGSE}":/dgse --cap-add=SYS_PTRACE dgse
fi
