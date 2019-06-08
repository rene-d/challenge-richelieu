// génère la table DAT_004898c0 de vérification du mot de passe
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;


int main(int argc, char *argv[])
{
    const byte *p;
    byte a;
    byte mot_de_passe[256];
    size_t i, length;

    if (argc != 2)
        exit(2);

    length = strlen(argv[1]);
    if (length > 255)
        exit(2);

    p = (const byte *)(argv[1]);
    a = 0x33;
    for (i = 0; i < length; ++i)
    {
        a = a ^ *p;
        mot_de_passe[i] = a;
        ++p;
    }
    mot_de_passe[i] = 0;

    printf("const byte DAT[] = {");
    for (i = 0; i <= length; ++i)
    {
        if (i % 8 == 0)
            printf("\n   ");
        printf(" 0x%02x,", mot_de_passe[i]);
    }
    printf("\n};\n");

    return 0;
}
