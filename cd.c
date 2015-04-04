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
        errno = 0;
        int etat;
        if(fork()){
			wait(&etat);
        }else{
            int reussite;
            reussite = chdir(argv[1]);
            if(reussite)
				afficherErrnoCd();
        }
    return 0;
}
