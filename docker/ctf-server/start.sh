#! /bin/sh

# compile shell.c avec gcc dockerisé
docker run -ti --rm -v $PWD:/data -w /data gcc:6 make

# construit l'image du server ssh
docker build --tag dgse:ctf-server .

./clean-ctf.sh 0
docker rm --force ctf-server

docker run --name ctf-server -d --rm -p 2222:22 -v /var/run/docker.sock:/var/run/docker.sock dgse:ctf-server

if [[ "$1" == "sh" ]]; then
    docker exec -ti ctf-server sh
fi
