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
validerListe(char *tampon);

int
validerFin(char *tampon);

int
estUneCommandeTsh(char *commande);

int
commandeCd(char *folder,char *name);

void 
commandeExit();

int
aUneIndirection(char **arguments);

char*
trouverIndirection(char **arguments);

void
setIndirectionDuProgramme(char *indirection,char **arguments,int tailleCommande);




#endif
