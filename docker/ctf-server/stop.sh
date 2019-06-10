#! /bin/sh

# supprime les containers de défi et le container serveur

if [[ $(uname) = Darwin ]]
then
    xargs=xargs
else
    xargs="xargs -r"
fi

docker ps -a --filter "label=defi" --format "{{.ID}}" --no-trunc | ${xargs} docker rm --force

docker ps -a --filter "name=ctf_server" --format "{{.ID}}" --no-trunc | ${xargs} docker rm --force
