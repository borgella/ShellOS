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
    if(errno == EACCES){ fprintf(stderr,"Permission Insuffisantes.\n");
    }else if(errno == ENOENT){  fprintf(stderr,"cd /inexistant \nRépertoire introuvable\n");
    }else if(errno == ENOTDIR){ fprintf(stderr,"Un des chemins n'est pas un répertoire.\n");
    }else if(errno == ENOMEM){  fprintf(stderr,"Il n'y a pas assez de memoire pour allouer une structure.\n");
    }else if(errno == ENAMETOOLONG){ fprintf(stderr,"L'argument est trop long que le chemin.\n");
    }else if(errno == ELOOP){  fprintf(stderr,"Trop de niveaux de liens ou de préfixes.\n");
    }
}

void
afficherErrnoCdir(){
    if(errno == EACCES){       fprintf(stderr,"Impossible de lire le chemin.\n");
    }else if(errno == ENOENT){ fprintf(stderr,"cd /inexistant \nRépertoire introuvable\n");
    }else if(errno == EFAULT){ fprintf(stderr,"Le tampon pointe sur une addresse illégale.\n");
    }else if(errno == EINVAL){ fprintf(stderr,"Le tampon pointe sur une adresse null.\n");
    }else if(errno == ENAMETOOLONG){ fprintf(stderr,"L'argument est trop long que le chemin.\n");
    }else if(errno == ELOOP){ fprintf(stderr,"Trop de niveaux de liens ou préfixes.\n");
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
          while((dp = readdir(repertoire)) != NULL){
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
        }else fprintf(stderr,"Erreur d'allocation.\n");
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
                    }                    
                }
             }
        }else{
			afficherErrnoCd();
			exit(1);
			}
     }else fprintf(stderr,"Répertoire introuvable.\n");
    chdir("..");
    closedir(repertoire);
}


void
removeRepertoire(char *folder){
    DIR *repertoire;
    struct dirent *dp;
    struct stat infos;
    int true;
    if ((repertoire = opendir(folder)) != NULL) {
        chdir(folder);   
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
            if(true) {
				true = stat(dp->d_name,&infos);
				if(!true){
					if(S_ISDIR(infos.st_mode)){
						removeRepertoire(dp->d_name);
						chmod(dp->d_name,0777);
						chdir("..");
						rmdir(dp->d_name);
					}
				}
            } 
        }
    }
    closedir(repertoire);
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
            if(true){
				if(strcmp(dp->d_name,arguments[i])==0){
					i++;
					if(i < taille){
						createFolder(arguments[i-1],arguments,taille);
					}
					reussite = chdir(arguments[taille-1]);
					if(!reussite){
                		 reussite = mkdir(arguments[taille],0777);
						 if(reussite == -1)
						     fprintf(stderr,"Impossible de créer le répertoire.\n"); 
					     else printf("Répertoire créé.\n");
					     exit(0);
					}else{
						fprintf(stderr,"Impossible de créer le répertoire.\n");
						exit(0);
					}			
				}		
			}
        }
     }
    chdir("..");
    closedir(repertoire);
}



int
leSizeEst(char *folder){
    DIR *repertoire;
    struct dirent *dp;
    struct stat infos;
    int true;
    char tampon[256];
	static int size = 1;
	if ((repertoire = opendir(folder)) != NULL) {
        true = chdir(folder);
        getcwd(tampon,256);
        if (!true) {
            while ((dp = readdir(repertoire))!= NULL) {
                true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
                if(true) {
                    true = stat(dp->d_name,&infos);
                    if (!true) {
                        if(S_ISDIR(infos.st_mode)){
							 size += infos.st_size; 
                             leSizeEst(dp->d_name);
                        }else{
							size += infos.st_size;
						}
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
    }else fprintf(stderr,"Répertoire introuvable.\n");				
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
							size++;
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


