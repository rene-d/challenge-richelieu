// calcule le mot de passe
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;

const byte DAT_004898c0[] =
{
/*0x4898c0:*/ 0x77, 0x30, 0x63, 0x26, 0x5d, 0x3a, 0x0e, 0x3b,
/*0x4898c8:*/ 0x0d, 0x4d, 0x2a, 0x1f, 0x2e, 0x1f, 0x2d, 0x4f,
/*0x4898d0:*/ 0x28, 0x51, 0x37, 0x7a, 0x14, 0x76, 0x20, 0x78,
/*0x4898d8:*/ 0x0f, 0x21, 0x4d, 0x21, 0x6c, 0x11, 0x00,
};

int main()
{
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

    printf("%s\n", mot_de_passe);

    /*
    printf("trouvé: %s\n", mot_de_passe);

    printf("vérification:\n");
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "./prog.bin '%s'", mot_de_passe);
    system(cmd);
    */

    return 0;
}
