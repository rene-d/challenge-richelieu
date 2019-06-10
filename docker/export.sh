#! /bin/bash

echo "#!/bin/sh" > docker-images.sh

docker image ls --no-trunc --format '{{.ID}} {{.Repository}}:{{.Tag}}' | while read id target
do
    echo "Saving ${target}"
    echo "docker tag ${id} ${target}" >> docker-images.sh
done

docker image ls --no-trunc --format '{{.ID}}' | xargs docker save -o docker-images.tar

echo "docker load -i docker-images.tar" >> docker-images.sh
chmod a+x docker-images.sh
