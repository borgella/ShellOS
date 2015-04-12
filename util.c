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
    int i = 0,taille = 8;
	char *listeCommande[] = {"lc","list","size","new","newdir",
							 "rmall","edit","fin",NULL};
	while(listeCommande[i]!= NULL){
		if((strcmp(listeCommande[i],uneCommande) == 0))
		 	 break;
		i++;	
	}						 
	return i < taille;
}


int
estDansLaListeDOptions(char *chaine){
    return (strncmp(chaine,"-d",2) == 0);
}

void
executerCommandeTsh(int argc,char **argv){
	printf("Verifions la taille %d\n",argc);
	if(strcmp(argv[0],"cd") == 0){
		commandeCd(argv);
	}else if(strcmp(argv[0],"cdir") == 0){
		commandeCdir(argv);
	}else if (strcmp(argv[0],"exit") == 0){
		commandeExit(argv);
	}
}	

void
commandeCd(int argc,char **argv){
	if(argc < 2 || argc > 2){
		fprintf(stderr,"Erreur,cette commande exige un et un seul argument.");
	}else {
		if(chdir(argv[1]))
			;//afficherErrnoCd();
	}
	
}

void
commandeCdir(int argc,char **argv){
	if(argc > 1){
		fprintf(stderr,"Erreur,cette commande ne prend aucun argument.");
	}else {
		char tampon[256];
        getcwd(tampon,256);
        if(tampon != NULL)
            printf("Répertoire courant : %s \n", tampon);
        else
            ;//afficherErrnoCdir();
	}
	
}

void
commandeExit(int argc,char **argv){
	if(argc > 1){
		fprintf(stderr,"Erreur,cette commande ne prend aucun argument.");
	}else {
		kill(getpid(),SIGKILL);
		exit(0);
	}
	
}
