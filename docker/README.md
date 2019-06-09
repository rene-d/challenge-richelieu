# Challenge Richelieu de la DGSE

https://www.challengecybersec.fr

## Liste des images Docker

### Images créées

REPOSITORY | TAG | Description
---------- | --- | -----------
dgse            | [stretch, latest](stretch/Dockerfile)         | Image avec tous les outils
dgse            | [defi1](ctf/Dockerfile) [defi2](ctf/Dockerfile) [defi3](ctf/Dockerfile)                      | Environnement CTF de defi1 defi2 defi3
dgse            | [ctf-server-defi1](ctf-server/Dockerfile) [ctf-server-defi2](ctf-server/Dockerfile) [ctf-server-defi3](ctf-server/Dockerfile)     | Serveur SSH pour un environnement de CTF
dgse            | [ctf-server-all](ctf-server/Dockerfile-all)   | Serveur SSH pour les trois CTF
alpine-gcc-make | [latest](gcc-make/Dockerfile)                 | Cross-compilation pour Linux

Le script [build-all.sh](build-all.sh) appelle toutes les commandes [docker build](https://docs.docker.com/engine/reference/commandline/build/) nécessaires pour créer les images ci-dessus.

☣️ La commande suivante permet de supprimer toutes les images créées pour le challenge :

```bash
docker image ls --filter "label=challenge_richelieu" --format "{{.ID}}" --no-trunc | xargs docker rmi
```

### Images utilisées

REPOSITORY | TAG | Description
---------- | --- | -----------
[buildpack-deps](https://hub.docker.com/_/buildpack-deps/)  | stretch       | base pour dgse:stretch
[debian](https://hub.docker.com/_/debian/)                  | stretch-slim  | base pour les machines de CTF
[alpine](https://hub.docker.com/_/alpine/)                  | latest        | base de alpine-gcc-make
[docker](https://hub.docker.com/_/docker/)                  | edge          | pour Docker in Docker
[bannsec/stegoveritas](https://hub.docker.com/r/bannsec/stegoveritas) | latest | outil de stéganographie

---
*rene-d juin 2019*
