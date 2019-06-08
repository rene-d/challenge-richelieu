# Challenge Richelieu de la DGSE - suite

https://www.challengecybersec.fr

## Liste des images Docker

### Images créées

REPOSITORY | TAG | Description
---------- | --- | -----------
dgse            | [stretch, latest](stretch/Dockefile)          | Image avec tous les outils
dgse            | [defi1](ctf/Dockerfile)                       | Environnement CTF du defi1
dgse            | [defi2](ctf/Dockerfile)                       | Environnement CTF du defi2
dgse            | [defi3](ctf/Dockerfile)                       | Environnement CTF du defi3
dgse            | [ctf-server-defi1](ctf-server/Dockerfile)     | Serveur SSH pour environnement de CTF de defi1
dgse            | [ctf-server-defi2](ctf-server/Dockerfile)     | Serveur SSH pour environnement de CTF de defi2
dgse            | [ctf-server-defi3](ctf-server/Dockerfile)     | Serveur SSH pour environnement de CTF de defi3
dgse            | [ctf-server-all](ctf-server/Dockerfile-all)   | Serveur SSH pour pour les trois CTF
alpine-gcc-make | [latest](gcc-make/Dockerfile)                 | Cross-compilation pour Linux

Le script [build-all.sh](build-all.sh) appelle toutes les commandes `docker build` nécessaires pour créer les images ci-dessus.

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

---
*rene-d juin 2019*
