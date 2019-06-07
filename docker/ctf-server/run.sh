#! /bin/sh

docker build --tag dgse:ctf-server .

docker run -ti --rm --privileged --name some-docker -d docker:dind

docker run --name ctf-server -d --rm --link some-docker:docker -p2222:22 -v /var/run/docker.sock:/var/run/docker.sock dgse:ctf-server
