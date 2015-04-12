#ifndef UTIL_H
#define UTIL_H
#include <sys/types.h>

int
nombreDeCaractereSaisi(char *tampon);

int 
tailleTableauDArguments(char *tampon);

char**
creerArguments(char* tampon);

int
caractereValide(char *tampon,int indiceTampon);

void
afficherTurboShell(char *tampon);

int
commandeValide(char **tampon,int taille);


int
estDansLaListeDeCommande(char * chaine);

int
estDansLaListeDOptions(char *chaine);

void
executerCommandeTsh(int argc,char **argv);	

void
commandeCd(char **argv);

void
commandeCdir(char **argv);

void
commandeExit(char **argv);


#endif
