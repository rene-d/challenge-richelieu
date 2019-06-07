#! /bin/bash

u()
{
    file=$1
    if [ ../../${defi}/${file} -nt ${defi}/${file} ]; then
        cp -p ../../${defi}/${file} ${defi}/${file}
    fi
}

b()
{
    defi=defi$1

    mkdir -p ${defi}
    u prog.bin
    u drapeau.txt

    docker build --tag dgse:${defi} --label defi --build-arg CTF_USER=${defi} .
}

echo
echo -e "\033[32mBuild des images\033[0m"
echo

docker image prune -f
for i in {1..3}; do b $i; done

echo
echo -e "\033[32mVérification des containers\033[0m"
echo

docker image ls --filter 'label=defi' --filter='reference=dgse' --format '{{.ID}}' | \
  xargs -t -n1 -I {} docker run -t --rm --hostname AttrapeLeDrapeau --network none --label defi {} ls -la
