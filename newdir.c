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
        errno = 0;
        char **arguments;
        int reussite;
        int taille = tailleTableauDArguments(argv[1]) - 1;
        arguments = creerArguments(argv[1]);
		if(taille == 0){
			chdir(arguments[taille-1]);
			reussite = mkdir(arguments[taille],0777);
			if(reussite == -1)
				fprintf(stderr,"Impossible de créer  le répertoire.\n");
			else
				printf("Repertoire crée.\n");
		}else{
			reussite = mkdir(arguments[taille],0777);
			if(reussite == -1)
				fprintf(stderr,"Impossible de créer  le répertoire.\n");
			else
				printf("Repertoire crée.\n");
			
			
		}

        return 0;
}

