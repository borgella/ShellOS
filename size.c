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

int main(int agrc, char*argv[]){
        int etat;
		int compteur = 0 ;
        int size = 0;
        if(fork()){
                wait(&etat);
        }else{
			char tampon[256];
			size = leSizeEst(argv[1]);
			if(size){
				compteur = nombreFichiers(argv[1]);
				chdir(argv[1]);
				getcwd(tampon,256);
				printf("Le répertoire %s contient %d fichiers pour un total de %d octets .\n",tampon,compteur,size);
			}else if (size == 0)
				printf("Le répertoire est vide.\n");
				
        }
	return 0;
}
