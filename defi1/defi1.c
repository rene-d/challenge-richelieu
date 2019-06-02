#include <stdio.h>
#include <stdlib.h>

int main()
{
    int choix;

    puts("#################################################");
    puts("##    Bienvenue dans ce lanceur (_wrapper_)    ##");
    puts("#################################################");
    puts("Ce logiciel vous permet de lancer ces programmes utiles simplement...");
    puts("Menu :");
    puts("   -> 1 : Affichage de la date et de l\'heure actuelle");
    puts("   -> 2 : Affichage du nombre de secondes écoulées depuis le 01/01/1970 (Epoch)");
    puts("   -> 3 : Affichage du train");
    puts("   -> 4 : Affichage du calendrier du mois en cours");

    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        system("date \'+Nous sommes le %d/%m/%Y et il est %H:%M:%S\'");
        break;
    case 2:
        system("date \'+Nombre de secondes depuis Epoch : %s\'");
        break;
    case 3:
        system("sl");
        break;
    case 4:
        system("cal");
        break;
    default:
        puts("Mauvais choix :-/");
        break;
    }

    return 0;
}
