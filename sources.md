# Assets

## Fichiers du challenge

Ce sont les fichiers qui ont été mis à disposition par les créateurs du challenge.

Fichier | Taille | MD5
------- | ------ | ----
[challenge1/web/Richelieu.pdf](challenge1/web/Richelieu.pdf) | 9737722 | `b90900747eed2a3c6095aab7185651e5`
[defi1/prog.bin](defi1/prog.bin)       |  8752 | `09b14c1d6114bcec12940a46e47f09b7`
[defi2/prog.bin](defi2/prog.bin)       | 10368 | `52ac18dc0d36b1c926c4220e0dada2de`
[defi3/prog.bin](defi3/prog.bin)       | 10392 | `645b9ec6c14ff92fb18fde1d911487f5`
[defi1/drapeau.txt](defi1/drapeau.txt) 🇫🇷 |   133 | `fdab957440cb01668dfff5864fd87f19`
[defi2/drapeau.txt](defi2/drapeau.txt) 🇫🇷 |   133 | `41f38dc256edbf3b8d82b2875c7d5c22`
[defi3/drapeau.txt](defi3/drapeau.txt) 🇫🇷 |   564 | `bdd43aa104db67e4a1c99c59e353c5a4`
le site [web](challenge1/web/) | |

## Elaboration du challenge

Reconstitution des fichiers source du challenge

Description | Fichier
----------- | -------
texte du PDF | [intro](challenge1/README.md#Texte-dintroduction)
1er dessin de Richelieu (taille origine: 2110 × 3508) | [Richelieu.jpg](challenge1/Richelieu-resized.jpg) 💬
clé privée RSA | [priv.key](challenge1/results/priv.key)
mot de passe du PNG | [motDePasseGPG.txt](challenge1/results/motDePasseGPG.txt)
2ème dessin de Richelieu (taille origine: 1562 × 2424) | [Richelieu.png](challenge1/lsb_RGB-resized.png) ⚠️
_crack-me_ pour le mot de passe de suite.zip | [prog.c](challenge2/prog.c)
générateur pour le _crack-me_ | [gen-table.c](challenge2/gen-table.c)
suite du challenge | [suite.txt](challenge1/results/suite.txt)
CTF défi1 | [defi1.c](defi1/defi1.c)
CTF défi2 | [defi2.c](defi2/defi2.c)
CTF défi3 | [defi3.c](defi3/defi3.c)
environnement AttrapeLeDrapeau | [Dockerfile](docker/ctf/Dockerfile)
serveur AttrapeLeDrapeau | [Dockerfile](docker/ctf-server/Dockerfile), [shell.c](docker/ctf-server/shell.c)

💬 _l'image d'origine est constituée des 445628 premiers octets de [data](challenge1/results/data), `dd if=data of=Richelieu.jpg bs=445628 count=1` pour la recréer._

⚠️ _image d'origine impossible à reconstruire puisque l'image dont on dispose a été altérée par stéganographie._

## Mots de passe utilisés

Origine | Passphrase
------- | ----------
mot de passe de Richelieu.zip                         | `DGSE{t.D=@Bx^A%n9FQB~_VL7Zn8z=:K^4ikE=j0EGHqI}`
mot de passe GnuPG de lsb_RGB.png.enc                 | `DGSE{Ti,%yei3=stlh_,5@pIrrMU.^mJC:luYbt1Qe_-Y}`
mot de passe de suite.zip                             | `DGSE{g456@g5112bgyfMnbVXw.llM}`
mot de passe ssh de defi1@defi1.challengecybersec.fr  | `DGSE{2f77c517b06f1cd1ce864f79f41f25ca8874413c8c1204f7ec9c6728c87f270a}`
mot de passe ssh de defi2@defi2.challengecybersec.fr  | `DGSE{H#M?W)el{0YZ-)77/C#ogrp}k4&EbP}`
mot de passe ssh de defi3@defi3.challengecybersec.fr  | `DGSE{?uo20tPO4(o=A=dX3njr2y{emZQodR}`

---
*rene-d juin 2019*
