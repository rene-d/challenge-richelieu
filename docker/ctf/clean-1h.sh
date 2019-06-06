#! /bin/bash

MAX_AGE=3600

if [ $(uname) = "Darwin" ]; then
    one_hour=$(date -u -r "$(($(date -u +%s) - ${MAX_AGE}))" +"%Y-%m-%dT%H:%M:%SZ")
else
    one_hour=$(date -d "@$(($(date --utc +%s) - ${MAX_AGE}))" +"%Y-%m-%dT%H:%M:%SZ")
fi
#one_hour="2019-06-06T21:18:52Z"

echo "one_hour  $one_hour"

docker ps --filter "label=defi" --format '{{.ID}}' | xargs -n1 docker container inspect --format='{{.ID}} {{.State.StartedAt}}' | while read id started_at
do
    if [[ ${one_hour} > ${started_at} ]]
    then
        echo "kill      ${started_at} too old (>${MAX_AGE} s)"
        docker container rm --force ${id}
    else
        echo "startedat ${started_at} ok"
    fi
done
