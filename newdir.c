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

void
createFolder(char* tampon,char **arguments,int taille);

int main(int agrc, char*argv[]){
    errno = 0;
    char **arguments;
    int reussite;
    int taille = tailleTableauDArguments(argv[1]) - 1;
    char tampon[256];
    getcwd(tampon,256);
    arguments = creerArguments(argv[1]);
	if(taille == 0){
		chdir(arguments[taille-1]);
		reussite = mkdir(arguments[taille],0777);
		if(reussite == -1)
			fprintf(stderr,"Impossible de créer  le répertoire.\n");
		else
			printf("Repertoire crée.\n");
	}else
		createFolder(tampon,arguments,taille);				
	return 0;
}

void
createFolder(char* tampon,char **arguments,int taille){
    DIR *repertoire;
    struct dirent *dp;
    int true;
    static int i = 0;
    static int reussite = 0;
    if ((repertoire = opendir(tampon)) != NULL) {
        chdir(tampon);
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
            if(true) {
				if(strcmp(dp->d_name,arguments[i])==0){
					i++;
					if(i < taille){
						createFolder(arguments[i-1],arguments,taille);
					}
					chdir(arguments[taille-1]);
					if(!reussite){
						reussite = mkdir(arguments[taille],0777);
						if(reussite == -1)
							fprintf(stderr,"Impossible de créer le répertoire.\n"); 
						else
							printf("Répertoire créé.\n");
						break;
					}			
				}   
			}
        }
     }
     closedir(repertoire);
}






/*
void
createFolder(char* tampon,char *folder,char *name){
    DIR *repertoire;
    struct dirent *dp;
    int true,reussite;
    if ((repertoire = opendir(tampon)) != NULL) {
        chdir(tampon);
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
            if(true) {
				if(strcmp(dp->d_name,folder)==0){
					chdir(folder);
					reussite = mkdir(name,0777);
					if(reussite == -1)
						fprintf(stderr,"Impossible de créer le repertoire.\n"); 
				     else
						printf("Repertoire crée.\n");
					 break;
					}   
				}
            }
        }
}
*/
