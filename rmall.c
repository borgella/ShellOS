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
    struct stat infos;
    int true;
	if(fork()){
		wait(&etat);
	}else{
		char tampon[256];
        true = stat(argv[1],&infos);
        if (!true) {
			if(S_ISDIR(infos.st_mode)){
				removeFile(argv[1]);
				removeRepertoire(argv[1]);
				chdir(argv[1]);
				chdir("..");
				getcwd(tampon,256);
				supprimer(tampon,argv[1]);
				printf("Répertoire supprimé.\n");
			}
         }else
			fprintf(stderr,"Imposside d'avoir les informations du fichier code d'erreur est : %d\n",errno);
    }
	return 0;
}

