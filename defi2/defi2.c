/*
 * Code source de prog.bin reconstitué avec Ghidra
 */

// pour compiler:
//  cc -z execstack -fno-stack-protector -no-pie defi2.c

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef unsigned char byte;
typedef unsigned long ulong;
typedef unsigned int uint;

bool verif(char *buffer, char *pcParm2) /* FUN_004006a6 */
{
    char *pcVar1;
    size_t len;
    int i;
    int nb_nombres;
    int nb_majuscules;
    int nb_minuscules;
    bool ok;

    ok = true;
    nb_minuscules = 0;
    nb_majuscules = 0;
    nb_nombres = 0;

    if (strcasestr(buffer, pcParm2) != 0 || strcasestr(pcParm2, buffer) != 0)
    {
        ok = false;
        puts("[-] le mot de passe est compris dans le login (ou l\'inverse)");
    }

    len = strlen(buffer);
    if (len < 8)
    {
        ok = false;
        puts("[-] mot de passe trop petit (moins de 8 caractères)");
    }

    i = 0;
    while (buffer[i] != '\0')
    {
        if (('`' < buffer[i]) && (buffer[i] < '{'))
        {
            nb_minuscules = nb_minuscules + 1;
        }
        if (('@' < buffer[i]) && (buffer[i] < '['))
        {
            nb_majuscules = nb_majuscules + 1;
        }
        if (('/' < buffer[i]) && (buffer[i] < ':'))
        {
            nb_nombres = nb_nombres + 1;
        }
        i = i + 1;
    }

    if (nb_nombres == 0)
    {
        ok = false;
        puts("[-] il n\'y a pas de nombre");
    }
    if (nb_majuscules == 0)
    {
        ok = false;
        puts("[-] il n\'y a pas de majuscule");
    }
    if (nb_minuscules == 0)
    {
        ok = false;
        puts("[-] il n\'y a pas de minuscule");
    }

    len = strlen(buffer);
    if (nb_minuscules + nb_majuscules + nb_nombres == (int)len)
    {
        ok = false;
        puts("[-] il n\'y a pas de caractère spécial");
    }

    return ok;
}

char *saisie(char *buffer) /* FUN_0040086d */
{
    bool ok;
    size_t len;
    char password[48];

    printf("login $ ");
    fgets(buffer, 1000, stdin);
    len = strlen(buffer);
    buffer[len - 1] = '\0';  /* supprime le \n final */

    printf("pass $ ");
    scanf("%s", password);

    len = strlen(buffer);
    if (10 < len)
    {
        puts("ATTENTION : le login est réduit à 10 caractères");
        buffer[10] = '\0';
    }

    ok = verif(password, buffer);
    if (ok == false)
    {
        buffer = NULL;
    }

    return buffer;
}

int main() /* FUN_00400932 */
{
    char buffer[1032];
    char *login;

    puts("************************************************");
    puts("** Vérification du couple login/mot de passe. **");
    puts("************************************************");
    login = saisie(buffer);
    if (login == NULL)
    {
        puts("Pas bon. Il vaudrait mieux utiliser un autre couple login/mot de passe");
    }
    else
    {
        printf("Okay, vous pouvez utiliser ce couple login/mot de passe pour le login %s.\n", login);
    }
    return 0;
}
