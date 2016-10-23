//
//  util.c
//  Created by Borgella, Jean-Mary on 2015-03-02.
//
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
#include "util.h"

//cette fonction creer la commande qui doit etre passe a execv
char**
creerArguments(char *tampon){
    int tailleArgument = tailleTableauDArguments(tampon) + 1; // pour ajouter le NULL
    int tailleChaine = nombreDeCaractereSaisi(tampon);
    int indiceTampon, indiceArgument, indiceChaine;
    char **arguments = malloc((tailleArgument + 1) * sizeof(char *));
    char *chaine = malloc(tailleChaine * sizeof(char));
		indiceArgument = indiceChaine = indiceTampon = 0;
        if (arguments != NULL && chaine != NULL) {
            while(tampon[indiceTampon] != '\0'){
                if(tampon[indiceTampon] != ' ' && tampon[indiceTampon] != '\n'){
                    chaine[indiceChaine++] = tampon[indiceTampon++];
                }else{
                    chaine[indiceChaine] = '\0';
                    arguments[indiceArgument] = malloc(indiceChaine * sizeof(char));
                    strcpy(arguments[indiceArgument++],chaine);
                    indiceChaine = 0;
                    indiceTampon++;
                }
            }
			arguments[indiceArgument] = NULL;
            free(chaine);
        }else
			{
				fprintf(stderr,"Erreur d'allocation,le code de retour est %d.\n",errno);
			}
    return arguments;
}
//cette fonction retourne la taille du tableau a prevoir pour la commande tape par l utilisateur
int
tailleTableauDArguments(char *tampon){
    int i = 0, j = 0;
        while(tampon[i++] != '\n'){
            if(tampon[i] == ' ')
                j++;
        }
        if(tampon[0]!='\n')
            j++;
    return j;
}
//cette methode permet d'allouer de la memoire necessaire selon le nombre de caracteres saisi
int
nombreDeCaractereSaisi(char *tampon){
    int i = 0;
    while(tampon[i] != '\0')
        i++;
   return i;
}

int
caractereValide(char *tampon,int indiceTampon){
    return tampon[indiceTampon] != ' ' && tampon[indiceTampon] != '\n' && tampon[indiceTampon] != '\0';
    
}

void
afficherTurboShell(char *tampon){
    if (tampon[0] != '\n'){
        printf("tsh>");
        
    }
}

int
commandeValide(char **tampon,int taille){
	int validerCommande = 0;
	if(estDansLaListeDeCommande(tampon[0])){
		if(strcmp(tampon[0],"fin") == 0){
			validerCommande = validerFin(tampon[1]);
		}else if(strcmp(tampon[0],"list") == 0 && taille >= 2){
			validerCommande = validerListe(tampon[1]);
		}else{ validerCommande = 1; }
	}
	return validerCommande;
}

int
estDansLaListeDeCommande(char *uneCommande){
    int i = 0,taille = 11;
	char *listeCommande[] = {"list","size","cdir","cd","new","newdir",
							 "rmall","exit","edit","fin","lc",NULL};
							 
	while(listeCommande[i]!= NULL){
	  if((strcmp(listeCommande[i],uneCommande) == 0))
			break;
	  i++;	
	}						 
	return i < taille;
}
int validerFin(char *tampon){
	return atoi(tampon) > 0;
}

int
validerListe(char *chaine){
    return (strncmp(chaine,"-d",2) == 0);
}
int
estUneCommandeTsh(char *commande){
    return ((strcmp(commande,"cd") == 0) || (strcmp(commande,"cdir") == 0) 
			|| (strcmp(commande,"exit") == 0));
}
int
commandeCd(char *folder,char *name){
	int retour = 0;
	DIR *repertoire;
    struct dirent *dp;
    int true;
    if ((repertoire = opendir(folder)) != NULL) {
        chdir(folder);
        while ((dp = readdir(repertoire))!= NULL) {
            true = strcmp(dp->d_name,".") != 0;
            if(true) {
				if(strcmp(dp->d_name,name)==0){
					chdir(name);
					retour++;
					break;
				}
            }
        }
    }
    closedir(repertoire);	
	return retour;
}
int
aUneIndirection(char **arguments){
	int i = 0,indirection = 0;
    while(arguments[i]!= NULL){
	  if((strcmp(arguments[i],">") == 0) || (strcmp(arguments[i],"<") == 0))
			indirection++;
	  i++;	
	}
	return indirection > 0 ;
}

char*
trouverIndirection(char **arguments){
	char *indirection;
	int i = 0;
    while(arguments[i]!= NULL){
	  if((strcmp(arguments[i],">") == 0) || (strcmp(arguments[i],"<") == 0)){
		 indirection = arguments[i];
		 break;
	  }
	  i++;	
	}
	return indirection ;
}

void
setIndirectionDuProgramme(char *indirection,char **arguments,int taille){
	if(strcmp(indirection,">") == 0){
		 freopen(arguments[taille-1],"w+",stdout);
	}else{
		freopen(arguments[1],"w+",stdin);
	}
}



