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
    int tailleCommande, etat;
    pid_t enfant;
    printf("tsh>");
    while(1)
    {
        fgets(tampon, LIMITE, stdin);
        tailleCommande = tailleTableauDArguments(tampon);
        if (tailleCommande >= 1) {
              arguments = creerArguments(tampon);
              if((strcmp(arguments[0],"cd") == 0) || (strcmp(arguments[0],"cdir") == 0) || ((strcmp(arguments[0],"exit") == 0))){
					executerCommandeTsh(tailleCommande,arguments);
					afficherTurboShell(tampon);											
			  }else
			  {
				  afficherTurboShell(tampon);
				  enfant = fork();
				  if(enfant < 0){
						fprintf(stderr,"Impossible de creer un nouveau processus");
						exit(1);
				   }
				  if(enfant){
					   wait(&etat);
				  }else if(enfant == 0){   
						    if(commandeValide(arguments,tailleCommande)){
								execve(arguments[0],arguments,NULL);
								fprintf(stderr,"Erreur d'execve \n");
							}else fprintf(stderr,"Programme introuvable.\n");
            
				}
			  }
                
        }else
            {
               printf("tsh>");
            }
    }
    return 0;
}



		
            
            
            
            
             
            
            
            
            
            
