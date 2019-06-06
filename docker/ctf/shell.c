#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *const args[] =
    {
        "/usr/local/bin/docker",
        "run",
        "--label", "defi",
        "--rm",
        "-ti",
        "--hostname", "AttrapeLeDrapeau",
        "--network", "none",
        "dgse:defi1",
        NULL
    };

    puts("\n\
Partie Wargame du CTF Richelieu\n\
\n\
Outils disponibles:\n\
*******************\n\
\n\
  * gdb (avec peda)\n\
  * python 2.7\n\
  * pwnlib\n\
  * checksec\n\
  * vim\n\
  * emacs\n\
  * nano\n\
  * ltrace\n\
  * strace\n\
  * ...\n\
\n\
ATTENTION : les connexions sont coupées et les fichiers sont détruits\n\
automatiquement au bout de 1 heure.\n\
Pensez à sauvegarder vos fichiers sur un autre poste pour ne pas les perdre.\n\
");

	int err = execv(args[0], args);
    if (err == -1)
    {
        fprintf(stderr, "Cannot start environement\n");
        exit(2);
    }

    return 0;
}
