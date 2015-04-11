//
//  util.c
//  Created by Borgella, Jean-Mary on 2015-03-02.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
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
//cette fonction retour la taille du tableau a prevoir pour la commande tape par l utilisateur
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
    if (tampon[0] != '\n')
        printf("tsh>");
}

int
commandeValide(char **tampon,int taille){
		if (taille <= 1)
			return estDansLaListeDeCommande(tampon[0]);
		else if(strncmp(tampon[0],"list",4) == 0)
			return estDansLaListeDOptions(tampon[1]);
	return 1;
}

int
estDansLaListeDeCommande(char *uneCommande){
    int i = 0,taille = 11;
	char *listeCommande[] = {"lc","list","size","cdir","new","newdir",
							 "rmall","exit","edit","fin","cd",NULL};
							 
		while(listeCommande[i]!= NULL){
			if((strcmp(listeCommande[i],uneCommande) == 0))
					break;
			i++;	
		}						 
	return ++i < taille;
}

int
estDansLaListeDOptions(char *chaine){
    return (strncmp(chaine,"-d",2) == 0);
}
