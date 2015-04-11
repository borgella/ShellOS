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
	char *chaine = "Le répertoire %s contient %d fichiers pour un total de %d octets.\n";
	int compteur = 0 ;
    int size = 0;
	char tampon[256];
	FILE *fichier = NULL;
	size = leSizeEst(argv[1]);
	if(size){
		compteur = nombreFichiers(argv[1]);
		chdir(argv[1]);
		getcwd(tampon,256);
		if(agrc < 4)
			printf(chaine,tampon,compteur,size);
		else if((strcmp(argv[2],">")) == 0){
			chdir("..");
			fichier = fopen(argv[agrc-1],"w+");
			if(fichier != NULL){
				fprintf(fichier,chaine,tampon,compteur,size);
			}
		}else { fprintf(stderr,"Signe de redirection invalide.\n");}
			
	}else if (size == 0) printf("Le répertoire est vide.\n");
	fclose(fichier);
	return 0;
}
