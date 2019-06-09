# Challenge Richelieu de la DGSE

https://www.challengecybersec.fr

## Liste des images Docker

### Images créées

REPOSITORY | TAG | Description
---------- | --- | -----------
dgse            | [hacking, hacking-stretch, latest](hacking/Dockerfile)         | Image avec tous les outils ⬄ la plate-forme de _hacking_
dgse            | [defi1](ctf/Dockerfile)                       | Environnement CTF de defi1
dgse            | [defi2](ctf/Dockerfile)                       | Environnement CTF de defi2
dgse            | [defi3](ctf/Dockerfile)                       | Environnement CTF de defi3
dgse            | [ctf-server-defi1](ctf-server/Dockerfile)     | Serveur SSH pour l'environnement CTF de defi1
dgse            | [ctf-server-defi2](ctf-server/Dockerfile)     | Serveur SSH pour l'environnement CTF de defi2
dgse            | [ctf-server-defi3](ctf-server/Dockerfile)     | Serveur SSH pour l'environnement CTF de defi3
dgse            | [ctf-server-all](ctf-server/Dockerfile-all)   | Serveur SSH pour les trois CTF †
alpine-gcc-make | [latest](gcc-make/Dockerfile)                 | Cross-compilation pour Linux ‡

Le script [build-all.sh](build-all.sh) appelle toutes les commandes [docker build](https://docs.docker.com/engine/reference/commandline/build/) nécessaires pour créer les images ci-dessus.

† Le challenge n'a pas de serveur similaire : chaque défi est hébergé sur une machine différente.

‡ La cross-compilation n'est pas nécessaire si la machine hôte est un Linux 64 bits. Elle pourrait se faire avec n'importe quel container, le choix de [Alpine](https://www.alpinelinux.org)+gcc correspond à un choix minimaliste en taille d'image et de... exécutable. En effet la libc qui vient avec est [musl](https://www.musl-libc.org), bien plus légère que la [glibc](https://www.gnu.org/software/libc/).

☣️ La commande suivante permet de supprimer toutes les images créées pour le challenge :
```bash
docker image ls --filter "label=challenge_richelieu" --format "{{.ID}}" --no-trunc | xargs docker rmi
```

### Images utilisées

REPOSITORY | TAG | Description
---------- | --- | -----------
[buildpack-deps](https://hub.docker.com/_/buildpack-deps/)  | stretch       | base pour dgse:hacking
[debian](https://hub.docker.com/_/debian/)                  | stretch-slim  | base pour les machines de CTF
[alpine](https://hub.docker.com/_/alpine/)                  | latest        | base de alpine-gcc-make
[docker](https://hub.docker.com/_/docker/)                  | edge          | pour Docker in Docker

---
*rene-d juin 2019*
