#! /bin/sh

# supprime les containers de défi vieux de plus d'une heure

MAX_AGE=${1:-3600}

if [ $(uname) = "Darwin" ]; then
    one_hour=$(date -u -r "$(($(date -u +%s) - ${MAX_AGE}))" +"%Y-%m-%dT%H:%M:%SZ")
else
    one_hour=$(date -d "@$(($(date --utc +%s) - ${MAX_AGE}))" +"%Y-%m-%dT%H:%M:%SZ")
fi

docker ps --filter "label=defi" --format '{{.ID}}' | xargs -r -n1 docker container inspect --format='{{.ID}} {{.Created}}' | while read id started_at
do
    if [ ${one_hour} \> ${started_at} ]
    then
#         echo "Remove  ${started_at} too old (>${MAX_AGE} s)"
        docker container rm --force ${id}
#     else
#         echo "Created ${started_at} ok"
    fi
done
