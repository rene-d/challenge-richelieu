// remplacement de login shell pour lancer un container Docker
// rene-d 2019

// Installation:
//  cc -o /usr/local/bin/ctfsh -O2 shell.c
//  echo /usr/local/bin/ctfsh >> /etc/shells
//  chsh -s /usr/local/bin/ctfsh defi1

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char container[256];

    char *const args[] =
    {
        "/usr/local/bin/docker",
        "run",
        "--label", "defi",
        "--rm",
        "-ti",
        "--hostname=AttrapeLeDrapeau",
        "--network=none",
        "--cap-add=SYS_PTRACE",
        container,
        NULL
    };

    const char *user = getenv("USER");
    if ((user == NULL) || (strncmp(user, "defi", 4) != 0))
    {
        user = "defi1";
    }
    snprintf(container, sizeof container, "dgse:%s", user);

    int err = execv(args[0], args);
    if (err == -1)
    {
        fprintf(stderr, "Cannot start environement\n");
        exit(2);
    }

    return 0;
}
