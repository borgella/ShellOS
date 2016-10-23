#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "util.h"
#define	 LIMITE 500

int main(int argc, char **argv)
{
    char tampon[LIMITE];
    char **arguments;
    char *indirection;
    int tailleCommande, etat,retour_methodes;
    pid_t enfant;
    printf("tsh>");
    fflush(stdout);
    while(1)
    {
        fgets(tampon, LIMITE, stdin);
        enfant = fork();
        if(enfant < 0)
        {
			fprintf(stderr,"impossible de creer de nouveau processus \n");
			exit(1);
		}
        else if(enfant == 0)
        {	
			tailleCommande = tailleTableauDArguments(tampon);
            if (tailleCommande >= 1) {
                arguments = creerArguments(tampon);
                if(commandeValide(arguments,tailleCommande)){
					retour_methodes = aUneIndirection(arguments);
					if(retour_methodes)
					{
						indirection = trouverIndirection(arguments);
						setIndirectionDuProgramme(indirection,arguments,tailleCommande);
					}
					if(estUneCommandeTsh(arguments[0]))
					{
						getcwd(tampon,256);
						if(strcmp(arguments[0],"cd") == 0){
							retour_methodes = commandeCd(tampon,arguments[1]);
							if(!retour_methodes)
								fprintf(stderr,"Repertoire inexistant.\n");
						}else if(strcmp(arguments[0],"cdir") == 0){
							if(tampon != NULL)
								printf("Répertoire courant : %s \n", tampon);
								fflush(stdout);
						}else{
							kill(enfant,SIGKILL);
						}
					 }else {
						 execve(arguments[0],arguments,NULL);
						 fprintf(stderr,"Erreur d'execve,les programmes ne se trouvent pas dans ce repertoires.\n");
					 }
                
                }else {
					if(strcmp(arguments[0],"fin") == 0)
						fprintf(stderr,"Argument Invalide.\n");
					else{
						fprintf(stderr,"Programme Invalide.\n");
					}	
				}
            }
            else
            {	
               printf("tsh>");
            }
            
        }
        else
        {   
			waitpid(enfant,&etat,0);
	    }
        afficherTurboShell(tampon);
        fflush(stdout);
    }
    return 0;
}
