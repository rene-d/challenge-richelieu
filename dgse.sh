#! /bin/bash

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
    docker exec -ti ${ID} /entrypoint bash
else
    echo "Starting the container"
    DGSE=$(cd $(dirname $0); pwd)
    docker run --name dgse --hostname dgse --rm -ti -v "${DGSE}":/dgse --cap-add=SYS_PTRACE dgse
fi
