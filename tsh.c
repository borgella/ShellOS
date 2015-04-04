#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "util.h"
#define	 LIMITE 500

int main(int argc, char **argv)
{
    char tampon[LIMITE];
    char **arguments;
    int tailleCommande, etat;
    pid_t enfant;

    printf("tsh>");
    while(1)
    {
        fgets(tampon, LIMITE, stdin);
        afficherTurboShell(tampon);
        enfant = fork();
        if(enfant)
        {
            wait(&etat);
        }
        else
        {   tailleCommande = tailleTableauDArguments(tampon);
            if (tailleCommande >= 1) {
                arguments = creerArguments(tampon);
                if(commandeValide(arguments,tailleCommande))
					execvp(arguments[0],arguments);
                else
                    fprintf(stderr,"Programme introuvable.\n");
            }
            else
            {
               printf("tsh>");
            }
        }
    }
    return 0;
}
