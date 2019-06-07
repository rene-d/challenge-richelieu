# Challenge Richelieu de la DGSE

https://www.challengecybersec.fr

## Plateforme d'exécution des Capture The Flag

Les connexions SSH sont containerisées avec des images très proches de celles créées par le script `build.sh`.

* Debian Stretch slim
* installation des mêmes packages, sans supplément
* ajout de pwntools et peda
* deux utilisateurs: defiX et defiX-drapeau
* les deux fichiers: prog.bin et drapeau.txt

## La connexion SSH

Pour que la connexion SSH à l'utilisateur defiX atterrisse dans un nouveau container à chaque fois, il est nécessaire de remplacer son login shell par le programme `shell.c` compilé.

---
*rene-d juin 2019*
