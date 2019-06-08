# Challenge Richelieu de la DGSE

https://www.challengecybersec.fr

## Environnement d'exécution des Capture The Flag

Les connexions SSH sont containerisées avec des [images](Dockerfile) très proches de celles créées par le script `build.sh`.

* [Debian](https://hub.docker.com/_/debian/) Stretch slim
* installation des mêmes packages, sans supplément
* ajout de [pwntools](https://github.com/Gallopsled/pwntools) et [peda](https://github.com/longld/peda)
* deux utilisateurs: defiX et defiX-drapeau
* les deux fichiers: `prog.bin` et `drapeau.txt`

## La connexion SSH

Pour que la connexion SSH à l'utilisateur defiX « atterrisse » à chaque fois dans un nouveau container, il est nécessaire d'appeler `docker run` à la place de `/bin/bash`. Voir [ctf-server](../ctf-server/README.md).

Les mots de passe du défi sont ceux de l'utilisateur defiX du host, pas ceux des users des containers de CTF (ils sont d'ailleurs désactivés).

---
*rene-d juin 2019*
