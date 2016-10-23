#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>
#include "fonction.h"

typedef struct Donne{
	FILE *fichierEdit;
	char *tampon;
	int  tailleTampon;
	int indice;
	int fin;
	char *nomFichier;
	pthread_mutex_t mutex;	
}Donne;

void
*saisirLesCaracteres(void *parametre);

void 
*modifierLeFichier(void *parametre);

char
*agrandirLeTableau(char *letableau,int taille);

void 
ecrireDansLeFichier(Donne *donnelocal);

void
viderTampon(Donne *donne);

void
ecrireDansLeFichier(Donne *donnelocal);

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int main(int agrc, char*argv[]){
	pthread_t threadlecture;
	pthread_t threadmodification;
        Donne *donne = malloc(sizeof(Donne));
	donne->fichierEdit = fopen(argv[1],"w+");
	donne->tailleTampon = 200;
	donne->tampon = malloc(donne->tailleTampon*sizeof(char));
	donne->fin = 1;
	donne->nomFichier = argv[1];
	
	
	if(donne == NULL || donne->tampon == NULL || donne->fichierEdit == NULL){
		if(donne->fichierEdit == NULL)
			fprintf(stderr,"Impossible de creer le fichier. \n"); 
		else	
			fprintf(stderr,"Impossible d'allouer de la memoire \n"); 
		exit(1);
	}
	
	pthread_mutex_init(&donne->mutex,NULL);
	pthread_create(&threadlecture,NULL,saisirLesCaracteres,donne);
	pthread_create(&threadmodification,NULL,modifierLeFichier,donne);
	pthread_join(threadlecture,NULL);
	pthread_join(threadmodification,NULL);
	free(donne->tampon);
	free(donne);	
	return 0;
}

void 
*saisirLesCaracteres(void *parametre){
	Donne *donnelocal = parametre;
	int ponctuation = 0,indice = 0,slash = 0;
	char caractere;
	while((caractere = fgetc(stdin))!= EOF){
	    if(indice == 0){
			if((islower(caractere)) && slash == 0)
				caractere = toupper(caractere);
		}
		if(caractere == '.' || caractere == '!' || caractere == '?'){
			ponctuation++;
			
		}else if(ponctuation && caractere != ' ' ){
			donnelocal->tampon[indice++] = ' ';
			if(islower(caractere))
				caractere = toupper(caractere);
				ponctuation = 0;
		}
		pthread_mutex_lock(&donnelocal->mutex);	
		if(indice < donnelocal->tailleTampon){	
			donnelocal->tampon[indice++] = caractere;
		}else{
			donnelocal->tampon = agrandirLeTableau(donnelocal->tampon,donnelocal->tailleTampon);
			donnelocal->tampon[indice++] = caractere;
			donnelocal->tailleTampon = donnelocal->tailleTampon * 2;
		}
		pthread_mutex_unlock(&donnelocal->mutex);
		if(caractere == '\n'){
			donnelocal->indice = indice;
			pthread_mutex_lock(&donnelocal->mutex);
			pthread_cond_signal(&condition);
			pthread_mutex_unlock(&donnelocal->mutex);
			indice = 0;
			slash++;
		}
		if(caractere == 0033)
			break;
		
	}//fin while
	donnelocal->fin = 0;
	donnelocal->indice = indice;
	pthread_mutex_lock(&donnelocal->mutex);
	pthread_cond_signal(&condition);
	pthread_mutex_unlock(&donnelocal->mutex);
	pthread_exit(NULL);
}

char
*agrandirLeTableau(char *letableau,int taille){
	char *ptr_tableau = calloc((taille*2),sizeof(char));
	int i ;
	for(i = 0; i < taille; i++){
		ptr_tableau[i] = letableau[i];
	}	
	return ptr_tableau;
}

void 
*modifierLeFichier(void *parametre){
	Donne *donnelocal = (Donne *) parametre;
	int  faire = 1;
	while(faire){
		pthread_mutex_lock(&donnelocal->mutex);
		pthread_cond_wait(&condition,&donnelocal->mutex);
		ecrireDansLeFichier(donnelocal);
		viderTampon(donnelocal);
		pthread_mutex_unlock(&donnelocal->mutex);
		faire = donnelocal->fin;
	}
	return NULL;
}

void 
ecrireDansLeFichier(Donne *donnelocal){
	donnelocal->fichierEdit = fopen(donnelocal->nomFichier,"a");
	if(donnelocal->fichierEdit != NULL)
		fprintf(donnelocal->fichierEdit,"%s",donnelocal->tampon);
	else 
		fprintf(stderr,"Erreur d'ouverture du fichier\n");
	fclose(donnelocal->fichierEdit);
}

void
viderTampon(Donne *donne){
	int i = 0;
	while(i < donne->indice)
		  donne->tampon[i++] = '\0';
}



