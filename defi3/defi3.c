/*
 * Code source de prog.bin reconstitué avec Ghidra
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


struct element
{
    char *nom;
    char *id;
};

void saisie_nom_element(struct element *element, int numero_element)       /* FUN_00400776 */
{
    size_t sVar1;
    char local_508[1280];

    printf("élément %d\t\t\tentrez nom $ ", numero_element);
    fgets(local_508, 1280, stdin);
    sVar1 = strlen(local_508);
    local_508[sVar1 - 1] = 0;

    sVar1 = strlen(local_508);
    element->nom = (char *) malloc(sVar1 + 1);
    strcpy(element->nom, local_508);
}

void saisie_id_element(struct element *element, int numero_element, int taille_id)    /* FUN_00400824 */
{
    size_t sVar1;
    char local_508[1280];

    printf("élément %d (%2d octets max)\tentrez id $ ", numero_element, taille_id);
    fgets(local_508, taille_id + 2, stdin);
    sVar1 = strlen(local_508);
    local_508[sVar1 - 1] = 0;
    element->id = (char *) malloc(taille_id + 1);
    strcpy(element->id, local_508);
}

int saisie_nombre(void) /* FUN_004008de */
{
    size_t sVar1;
    char local_108[256];

    fgets(local_108, 256, stdin);
    sVar1 = strlen(local_108);
    local_108[sVar1 - 1] = 0;
    return atoll(local_108);
}

void affichage(struct element **elements, int nombre_elements) /* FUN_00400930 */
{
    int numero;

    puts("~~~~~~~~~~~~~");
    puts("~~ élément ~~");
    puts("~~~~~~~~~~~~~");
    numero = 0;
    while (numero < nombre_elements)
    {
        printf("  élément[%d]\t-> nom : %s\n", numero, elements[numero]->nom);
        printf("  élément[%d]\t-> id : %s\n\n", numero, elements[numero]->id);
        numero = numero + 1;
    }
    return;
}

void nouvel_element(struct element **elements, int *nombre_elements, int taille_id) /* FUN_004009dc */
{
    struct element *element;

    if (*nombre_elements == 29)
    {
        puts("Plus de place pour un nouvel élément");
    }
    else
    {
        element = (struct element *) malloc(sizeof(struct element));

        elements[*nombre_elements] = element;

        saisie_nom_element(elements[*nombre_elements], *nombre_elements);
        saisie_id_element(elements[*nombre_elements], *nombre_elements, taille_id);

        *nombre_elements = *nombre_elements + 1;
    }
}

int choix_menu(void) /* FUN_00400a9e */
{
    int nombre;
    int choix;

    puts("Que voulez-vous faire ?\n"
         "  -> 1) nouvel élément\n"
         "  -> 2) affichage\n"
         "  -> 3) détruire un élément\n"
         "  -> 4) changer de nom\n"
         "  -> 5) changer d\'id\n"
         "  -> 6) sortie");
    printf("choix $ ");
    nombre = saisie_nombre();
    if ((nombre < 1) || (5 < nombre))
    {
        choix = 6;
    }
    else
    {
        choix = nombre;
    }
    return choix;
}

int main(int argc, char **argv) /* FUN_00400ae8 */
{
    size_t sVar1;
    int nombre_elements;
    char saisie[1284];
    int quoi;
    int numero;
    int choix;
    struct element **elements;
    int taille_id;

    elements = (struct element **) malloc(30 * sizeof(struct element *)); /* 0xf0 */

    nombre_elements = 0;
    taille_id = 0;
    if (1 < argc)
    {
        taille_id = atoi(argv[1]);
    }
    if ((taille_id < 2) || (100 < taille_id))
    {
        taille_id = 50;
    }

    puts("***************************************************");
    puts("***    Bienvenue dans la gestion d\'éléments     ***");
    puts("***                                             ***");
    printf("***   NB : Taille de l\'ID : %2d octets           ***\n", taille_id);
    puts("***        Vous pouvez mettre la taille         ***");
    puts("***        en paramètre pour la changer         ***");
    puts("***************************************************");

    while (true)
    {
        choix = choix_menu();

        switch (choix)
        {
        // nouvel élément
        case 1:
            nouvel_element(elements, &nombre_elements, taille_id); /* FUN_004009dc */
            break;

        // affichage
        case 2:
            affichage(elements, nombre_elements);
            break;

        // détruire un élément
        case 3:
            printf("lequel $ ");
            numero = saisie_nombre();
            if ((-1 < numero) && (numero < nombre_elements))
            {
                printf("quoi (id : 1   nom : 2) $ ");
                quoi = saisie_nombre();
                if (quoi == 1)
                {
                    free(elements[numero]->id);
                }
                if (quoi == 2)
                {
                    free(elements[numero]->nom);;
                }
            }
            puts("");
            break;

        // changer de nom
        case 4:
            printf("lequel $ ");
            numero = saisie_nombre();
            if ((-1 < numero) && (numero < nombre_elements))
            {
                printf("élément %d\tentrez nom $ ", numero);
                fgets(saisie, 9, stdin);
                sVar1 = strlen(saisie);
                saisie[sVar1 - 1] = 0;
                strcpy(elements[numero]->nom, saisie);
            }
            puts("");
            break;

        // changer d'id
        case 5:
            printf("lequel $ ");
            numero = saisie_nombre();
            if ((-1 < numero) && (numero < nombre_elements))
            {
                printf("élément %d\tentrez id $ ", numero);
                fgets(saisie, taille_id + 2, stdin);
                sVar1 = strlen(saisie);
                saisie[sVar1 - 1] = 0;
                strcpy(elements[numero]->id, saisie);
            }
            puts("");
            break;

        default:
            goto sortie;
            break;
        }
    }

sortie:
    puts("Au revoir !");
    return 0;
}
