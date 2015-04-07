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
createFile(char *tampon,char *folder,char *name);

int main(int agrc, char*argv[]){
    int etat;
    //DIR *dp;
    errno = 0;
    if(fork()){
         wait(&etat);
    }else{
         char **arguments;
         int reussite;
         int taille = tailleTableauDArguments(argv[1])-1 ;
         char tampon[256];
         getcwd(tampon,256);
         arguments = creerArguments(argv[1]);
         if(taille == 0){
              reussite = open(arguments[1],0777);
              if(reussite == -1)
                   fprintf(stderr,"Impossible de créer le fichier.\n");
			  else
				   printf("Fichier crée.\n");
         }else{
			 createFile(tampon,arguments[taille-1],arguments[taille]);	
         }
     }

   return 0;
}

void
createFile(char* tampon,char *folder,char *name){
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
					reussite = open(name,0777);
					if(reussite == -1)
						fprintf(stderr,"Impossible de créer le fichier.\n"); 
				     else
						printf("Fichier crée.\n");
					 break;
					}   
				}
            }
        }
}

