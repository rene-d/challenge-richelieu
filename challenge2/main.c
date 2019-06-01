#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
typedef unsigned long ulong;
typedef unsigned int uint;

const byte DAT_004898c0[] =
{
/*0x4898c0:*/ 0x77, 0x30, 0x63, 0x26, 0x5d, 0x3a, 0x0e, 0x3b,
/*0x4898c8:*/ 0x0d, 0x4d, 0x2a, 0x1f, 0x2e, 0x1f, 0x2d, 0x4f,
/*0x4898d0:*/ 0x28, 0x51, 0x37, 0x7a, 0x14, 0x76, 0x20, 0x78,
/*0x4898d8:*/ 0x0f, 0x21, 0x4d, 0x21, 0x6c, 0x11, 0x00, 0x2e,
/*0x4898e0:*/ 0x2e, 0x2f, 0x63, 0x73, 0x75, 0x2f, 0x6c, 0x69,
/*0x4898e8:*/ 0x62, 0x63, 0x2d, 0x73, 0x74, 0x61, 0x72, 0x74,
/*0x4898f0:*/ 0x2e, 0x63, 0x00, 0x46, 0x41, 0x54, 0x41, 0x4c,
/*0x4898f8:*/ 0x3a, 0x20, 0x6b, 0x65, 0x72, 0x6e, 0x65, 0x6c,
/*0x489900:*/ 0x20, 0x74, 0x6f, 0x6f, 0x20, 0x6f, 0x6c, 0x64,
/*0x489908:*/ 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

ulong FUN_00400aae(const byte *pbParm1)
{
    int iVar1;
    ulong uVar2;
    ulong uVar3;
    byte bVar4;
    long lVar5;
    const byte *pbVar6;
    byte bVar7;

    lVar5 = -1;
    pbVar6 = pbParm1;
    do
    {
        if (lVar5 == 0)
            break;
        lVar5 = lVar5 + -1;
        bVar4 = *pbVar6;
        pbVar6 = pbVar6 + 1;
    } while (bVar4 != 0);

    uVar2 = 0;
    if (lVar5 == -0x20)
    {
        bVar4 = *pbParm1;
        if (bVar4 != 0)
        {
            pbVar6 = DAT_004898c0;
            pbParm1 = pbParm1 + 1;
            uVar3 = 1;
            bVar7 = 0x33;
            do
            {
                iVar1 = (int)uVar3;
                uVar3 = 0;
                if (iVar1 != 0)
                {
                    uVar3 = (ulong)((bVar4 ^ bVar7) == *pbVar6);
                }
                bVar7 = *pbVar6;
                bVar4 = *pbParm1;
                pbVar6 = pbVar6 + 1;
                pbParm1 = pbParm1 + 1;
            } while (bVar4 != 0);
            return uVar3;
        }
        uVar2 = 1;
    }
    return uVar2;
}

void crack()
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

    printf("trouvé: %s %s\n", mot_de_passe, FUN_00400aae(mot_de_passe) ? "OK" : "KO");
}

int main(int iParm1, char *puParm2[]) /*FUN_00400b20*/
{
    uint uVar1;
    ulong uVar2;

    crack();

    if (iParm1 < 2)
    {
        printf("usage : %s <mot de passe>\n", *puParm2);
        uVar2 = 2;
    }
    else
    {
        uVar1 = FUN_00400aae((byte *)puParm2[1]);
        uVar2 = (ulong)uVar1;
        if (uVar1 == 0)
        {
            puts("Mauvais mot de passe");
        }
        else
        {
            puts("Bravo ! Vous pouvez utiliser ce mot passe pour la suite ;-)");
            uVar2 = 0;
        }
    }
    return uVar2;
}
