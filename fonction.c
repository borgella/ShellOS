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
afficherErrnoCd(){
    if(errno == EACCES){
        fprintf(stderr,"Permission Insuffisantes.\n");
    }else if(errno == ENOENT){
        fprintf(stderr,"cd /inexistant \nRépertoire introuvable\n");
    }else if(errno == ENOTDIR){
        fprintf(stderr,"Un des chemins n'est pas un répertoire.\n");
    }else if(errno == ENOMEM){
        fprintf(stderr,"Il n'y a pas assez de memoire pour allouer une structure.\n");
    }else if(errno == ENAMETOOLONG){
        fprintf(stderr,"L'argument est trop long que le chemin.\n");
    }else if(errno == ELOOP){
        fprintf(stderr,"Trop de niveaux de liens ou de préfixes.\n");
    }
}

void
afficherErrnoCdir(){
    if(errno == EACCES){
        fprintf(stderr,"Impossible de lire le chemin.\n");
    }else if(errno == ENOENT){
        fprintf(stderr,"cd /inexistant \nRépertoire introuvable\n");
    }else if(errno == EFAULT){
        fprintf(stderr,"Le tampon pointe sur une addresse illégale.\n");
    }else if(errno == EINVAL){
        fprintf(stderr,"Le tampon pointe sur une adresse null.\n");
    }else if(errno == ENAMETOOLONG){
        fprintf(stderr,"L'argument est trop long que le chemin.\n");
    }else if(errno == ELOOP){
        fprintf(stderr,"Trop de niveaux de liens ou préfixes.\n");
    }
}

void
liste(char *tampon){
        DIR *repertoire;
        struct dirent *dp;
        int true;
        if((repertoire = opendir(tampon)) != NULL ){
                while((dp = readdir(repertoire)) != NULL){
                        true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
                        if(true)
                                printf("%s\n",dp->d_name);
                }
        }
        closedir(repertoire);
}

void
listeAvecMoinsD(char *tampon){
        DIR *repertoire;
        struct dirent *dp;
        struct stat infos;
        int true;
        if((repertoire = opendir(tampon)) != NULL){
                printf("%s\n",tampon);
                true = chdir(tampon);
                if(!true){
                    while ((dp = readdir(repertoire)) != NULL){
						true = (strcmp(dp->d_name,"..") != 0) && (strcmp(dp->d_name,".") != 0);
						if(true){
							true = stat(dp->d_name, &infos);
							if(!true){
								if(S_ISDIR(infos.st_mode))
									listeAvecMoinsD(dp->d_name);
								else
									printf("%s \n", dp->d_name);
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
    chdir("..");
    closedir(repertoire);
}

char**
creerArguments(char *tampon){
    int tailleChaine = strlen(tampon);
    int tailleArgument = tailleTableauDArguments(tampon);
    int indiceTampon, indiceArgument, indiceChaine,tiret;
    indiceArgument = indiceChaine = indiceTampon = tiret = 0;
    char **arguments = malloc(tailleArgument * sizeof(char *));
    char *chaine = malloc(tailleChaine * sizeof(char));
		if (arguments != NULL && chaine != NULL) {
            while(indiceTampon < strlen(tampon)){
                if(tampon[indiceTampon] != '/'){
                    chaine[indiceChaine++] = tampon[indiceTampon++];
                }else{
                    chaine[indiceChaine] = '\0';
                    arguments[indiceArgument] = malloc(indiceChaine * sizeof(char));
                    strcpy(arguments[indiceArgument++],chaine);
                    indiceChaine = 0;
                    indiceTampon++;
				}
            }
             chaine[indiceChaine] = '\0';
             arguments[indiceArgument] = malloc(indiceChaine * sizeof(char));
             strcpy(arguments[indiceArgument++],chaine);
             free(chaine);
        }else{
             fprintf(stderr,"Erreur d'allocation.\n");
        }

   return arguments;
}

int
tailleTableauDArguments(char *tampon){
    int i = 0, j = 0;
      while(i < strlen(tampon)){
         if(tampon[i] == '/')
             j++;
         i++;
      }
      j++;
    return j;
}

void
removeFile(char *folder){
    DIR *repertoire;
    struct dirent *dp;
    struct stat infos;
    int true;
    
    if ((repertoire = opendir(folder)) != NULL) {
        true = chdir(folder);
        if (!true) {
            while ((dp = readdir(repertoire))!= NULL) {
                true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
                if(true) {
                    true = stat(dp->d_name,&infos);
                    if (!true) {
                        if (S_ISDIR(infos.st_mode))
                             removeFile(dp->d_name);
                        else
                            unlink(dp->d_name);
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
    }else
        fprintf(stderr,"Répertoire introuvable.\n");
    
    chdir("..");
    closedir(repertoire);
}


void
removeRepertoire(char *folder){
    DIR *repertoire;
    struct dirent *dp;
    int true;
    if ((repertoire = opendir(folder)) != NULL) {
        chdir(folder);
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
            if(true) {
                rmdir(dp->d_name);
            }
        }
    }
}

void
supprimer(char *folder,char *name){
    DIR *repertoire;
    struct dirent *dp;
    int true;
    if ((repertoire = opendir(folder)) != NULL) {
        chdir(folder);
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
            if(true) {
				if(strcmp(dp->d_name,name)==0){
					chmod(dp->d_name,0777);
					rmdir(dp->d_name);
				}
            }
        }
    }
    closedir(repertoire);
}

int
leSizeEst(char *folder){
    DIR *repertoire;
    struct dirent *dp;
    struct stat infos;
    int true;
	static int size = 0;
    if ((repertoire = opendir(folder)) != NULL) {
        true = chdir(folder);
        if (!true) {
            while ((dp = readdir(repertoire))!= NULL) {
                true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
                if(true) {
                    true = stat(dp->d_name,&infos);
                    if (!true) {
                        if (S_ISDIR(infos.st_mode))
                             leSizeEst(dp->d_name);
                        else
							size += infos.st_size;
						
                    }else{
						fprintf(stderr,"Impossible de lire les infos du fichier.\n");
						break;
					}
                    
                }
            }
        }else{
			afficherErrnoCd();
			exit(1);
		}
    }				
    chdir("..");
    closedir(repertoire);
	return size;
}

int
nombreFichiers(char *folder){
    DIR *repertoire;
    struct dirent *dp;
    struct stat infos;
    int true;
	static int size = 0;
    if ((repertoire = opendir(folder)) != NULL) {
        true = chdir(folder);
	    if (!true) {
            while ((dp = readdir(repertoire))!= NULL) {
                true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
                if(true) {
                    true = stat(dp->d_name,&infos);
                    if (!true) {
                        if (S_ISDIR(infos.st_mode)){
							nombreFichiers(dp->d_name);
						}else
							size++;
					}
                    
                }
            }
        }
    }
    chdir("..");
    closedir(repertoire);
	return size;
}
