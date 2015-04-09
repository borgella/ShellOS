#ifndef FONCTION_H
#define FONCTION_H
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
void
afficherErrnoCd();

void
afficherErrnoCdir();

void
liste(char *argv);

void
listeAvecMoinsD(char *argv);

char**
creerArguments(char *tampon);

int
tailleTableauDArguments(char *tampon);

void
supprimer(char *folder,char *name);

void
removeFile(char *folder);

void
removeRepertoire(char *folder);

int
leSizeEst(char *folder);

int
nombreFichiers(char *folder);


void
createFolder(char* tampon,char **arguments,int taille);

#endif
