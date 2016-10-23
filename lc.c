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
#define LIMITE 256

void
lc(char *tampon);

int main(int agrc, char*argv[]){
	char tampon[LIMITE];
	getcwd(tampon,256);
    lc(tampon);
    return 0;
}

void
lc(char *tampon){
   DIR *repertoire;
   struct dirent *dp;
   struct stat infos;
   int reussite;
   if((repertoire = opendir(tampon)) != NULL){
      reussite = chdir(tampon);
      if(!reussite){
          while((dp = readdir(repertoire)) != NULL){
			  reussite = (strcmp(dp->d_name,"..") != 0) && (strcmp(dp->d_name,".") != 0);
			  if(reussite){
				  reussite = stat(dp->d_name, &infos);
				  if(!reussite){
					 if(S_ISREG(infos.st_mode)){
					    printf("Sorry Programm not Supported... !\n");
					    break;
					   } 
				  }else{
						fprintf(stderr,"Impossible de lire les informations du fichier.\n");
						break;
				  }
			   }
		    }  
	  }else{
			afficherErrnoCd();
			exit(1);
		}
    }	
    closedir(repertoire);
}
