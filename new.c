#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include "fonction.h"

int main(int agrc, char*argv[]){
        int etat;
        errno = 0;
        if(fork()){
                wait(&etat);
        }else{
                char **arguments;
                int reussite;
                int taille = tailleTableauDArguments(argv[1]) - 1;
                arguments = creerArguments(argv[1]);
                if(taille == 1){
                        reussite = open(arguments[1],0777);
                        if(reussite == -1)
                            fprintf(stderr,"Impossible de créer le fichier.\n");
						else
							printf("Fichier crée.\n");
                }else{
                        chdir(arguments[taille-1]);
                        reussite = open(arguments[taille],0777);
                        if(reussite == -1)
                                fprintf(stderr,"Impossible de créer le fichier.\n");
						else
							printf("Fichier crée.\n");	
                }
        }

        return 0;
}
