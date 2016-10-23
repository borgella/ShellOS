#include <stdio.h>
#include <signal.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include "fonction.h"

int
trouverLeFichierACompter(char *folder,char *name);

int 
nombreLigne(FILE *fichier);

void
afficherNombreDeLignes(int debut,FILE *fichier);

int main(int agrc, char*argv[]){
	FILE *fichier = NULL;
    char **arguments;
    char tampon[256];
    int nombredelignes;
    int taille = tailleTableauDArguments(argv[2]);
    arguments = creerArguments(argv[2]);
    int debut = 0;
	if(taille > 1)
	{ // traitement chemin absolu
		if(trouverLeFichierACompter(arguments[taille-2],arguments[taille-1]))
		{
			fichier = fopen(arguments[taille-1],"r");
			nombredelignes = nombreLigne(fichier);
			debut = nombredelignes - atoi(argv[1]);
			if(debut < 0){
				fprintf(stderr,"Erreur argument plus grand que nombre de lignes\n");
				exit(1);
			}
			afficherNombreDeLignes(debut,fichier);
		}else fprintf(stderr,"Fichier introuvable. \n");
	}
	else 
	{ // traitement chemin relatif
		getcwd(tampon,256);
		if(trouverLeFichierACompter(tampon,arguments[0]))
		{
			fichier = fopen(arguments[0],"r");
			nombredelignes = nombreLigne(fichier);
			debut = nombredelignes - atoi(argv[1]);
			if(debut < 0){
				fprintf(stderr,"Erreur argument plus grand que nombre de lignes\n");
				exit(1);
			}
			afficherNombreDeLignes(debut,fichier);
		}else fprintf(stderr,"Fichier introuvable. \n");
	}
						
	return 0;
}

int
trouverLeFichierACompter(char *folder,char *name){
	int retour = 0;
    DIR *repertoire;
    struct dirent *dp;
    int true;
    if ((repertoire = opendir(folder)) != NULL){
        chdir(folder);
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0;
            if(true) {
				if(strcmp(dp->d_name,name)==0){
					retour = 1;
				}
            }
        }
    }else fprintf(stderr,"Impossible d'ouvrir le repertoire.\n"); 

    closedir(repertoire);
	return retour;
}
int 
nombreLigne(FILE *fichier){
	int nombre = 0, slash = 0, caractere;
 	while((caractere = fgetc(fichier))!= EOF){
		if( caractere == '\n' && slash == 0){
			nombre++;
			slash++;
		}else slash = 0;
	} 
	return nombre;
}

void
afficherNombreDeLignes(int debut,FILE *fichier){
	rewind(fichier);
	char * une_ligne = NULL;
    size_t longueur = 0;
    int compteur = 0;
    while(getline(&une_ligne, &longueur, fichier) != -1){ 
		if(compteur >= debut)
			printf("%s",une_ligne);
		compteur++;	
    }
}
