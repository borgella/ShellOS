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
        errno = 0;
        if(fork()){
                wait(&etat);
        }else{
            char tampon[256];
            getcwd(tampon,256);
            if(tampon != NULL)
                printf("Répertoire courant : %s \n", tampon);
            else
                afficherErrnoCdir();
        }
        return 0;
}
