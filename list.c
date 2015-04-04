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
#define  LIMITE 256

int main(int argc, char*argv[]){
        int etat;
        char tampon[LIMITE];
        getcwd(tampon,LIMITE);
        if(fork()){
                wait(&etat);
        }else{
                if(argc < 2){
                        printf("Fichiers de %s \n",tampon);
                        liste(tampon);
                }else{
                        listeAvecMoinsD(tampon);
                }
        }
        return 0;
}
