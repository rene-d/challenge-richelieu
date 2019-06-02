# Challenge Richelieu de la DGSE - suite

https://www.challengecybersec.fr


## Analyse de binaire

Le programme ELF a été compilé en statique (aka. `gcc -static prog.c`):
```
root@dgse:/dgse/challenge2# ldd prog.bin
	not a dynamic executable
```
Sa taille (738384 octets) en est aussi une indication.

Ce choix a été - certainement - fait afin de compliquer le désassemblage: la fonction `main()` est beaucoup plus difficile à repérer.

J'ai utilisé une méthode triviale pour analyser ce qu'il se passe lorsque on lance sans et avec un argument sur la ligne de commandes: consigner tout ce qu'il se passe avec une exécutation pas-à-pas dans gdb. A la première différence, c'est le traitement de argc/argv.

Pour déterminer le point d'entrée (_entry point_):
```
root@dgse:/dgse/challenge2# gdb -nx -q prog.bin
Reading symbols from prog.bin...(no debugging symbols found)...done.
(gdb) info files
Symbols from "/dgse/challenge2/prog.bin".
Local exec file:
	`/dgse/challenge2/prog.bin', file type elf64-x86-64.
	Entry point: 0x400990
	0x0000000000400190 - 0x00000000004001b0 is .note.ABI-tag
    ...
```

Créer un fichier `.gdbinit` comme suit:
```
file /dgse/challenge2/prog.bin
#set logging file output.txt
#set logging on
set disassemble-next-line on
show disassemble-next-line
display /x $rax
display /x $rbx
display /x $rcx
display /x $rdx
break *0x400990
#break *0x400b80
run
```
puis exécuter la commande bash:
```bash
(echo si; sleep 1; while pgrep prog.bin >/dev/null; do echo si; done) | gdb -q
```

En redirigeant la sortie standard dans un fichier et jouant avec la commande `run` pour rajouter un argument, on peut comparer les deux exécutions. Les logs sont filtrés par le script Python `filtre-gdb.py` pour ne garder que le code assembleur.

On voit que la fonction `main()` est selon toute vraissemblance à 0x00400b20. Charger le fichier dans [Ghidra](https://ghidra-sre.org), aller à cette adresse et on récupère le pseudo-code C. Il faut peu d'efforts pour le faire fonctionner.

## Reverse-engineering

Il faut comprendre ce que fait le programme, et heureusement, ce n'est pas bien compliqué.

Pour que le mot de passe soit valide, il faut que:
* la longueur soit **30 octets** (premier `do-while` et le `if (lVar5 == -0x20)` de la fonction `FUN_00400aae()`)
* que les caractères du mot de passe **correspondent** à la succession de [xor](https://fr.wikipedia.org/wiki/Fonction_OU_exclusif) faits dans le second `do-while`. Ces `xor` sont faits avec une valeur initiale (`0x33`) puis avec les octets du tableau `DAT_004898c0`.

Le code pour calculer le mot de passe qui va fonctionner est simple:
```C
    const byte *p;
    byte a;
    byte mot_de_passe[32];
    int i;

    p = DAT_004898c0;
    a = 0x33;
    for (i = 0; i < 30; ++i)
    {
        mot_de_passe[i] = a ^ *p;
        a = *p;
        ++p;
    }
    mot_de_passe[i] = 0;
```

Le programme [main.c](src/main.c) est une version reconstituée et compilable de `prog.bin`.

Le programme [crack.c](crack.c) reconstitue le mot de passe, l'affiche et le vérifie avec `prog.bin`.

Le mot de passe est donc: `DGSE{g456@g5112bgyfMnbVXw.llM}`

## Suite du challenge

On peut donc dézipper `suite.zip` (cf. [étape 4](../challenge1/README.md#Extraction-des-fichiers-de-l'archive-ZIP) de la première partie). Le fichier `suite.txt` contient les instructions pour continuer le challenge, qui va se passer sur une machine distante.

```
Suite du challenge Richelieu :

ssh defi1.challengecybersec.fr -l defi1 -p 2222

mot de passe : DGSE{2f77c517b06f1cd1ce864f79f41f25ca8874413c8c1204f7ec9c6728c87f270a}
```

On peut remarquer que le mot de passe est vraisemblablement construit avec un SHA256.

[Suite...](../defi1/README.md)

---
*rene-d 26 mai 2019*
