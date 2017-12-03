

#include <stdio.h>
#include <string.h>

#include "../inc/tache.h"

void emulateur(taskStruct tache){
	printf("emulateur : commande = %s\n",tache.commande);
	// decomposition de la commande 
	char *pch = strtok (tache.commande, " ");
	if (strlen(pch) == 0){
		printf("commande incorrecte\n");
		return; 
	}
	for (int i = 0 ; i < MAX_PARAM ; i++){
		strcpy(tache.parametres[i],"");
	}
	int ptrParam = 0;
	while (pch != NULL){
		pch = strtok(NULL," ");
		if (pch != NULL){
			strcpy(tache.parametres[ptrParam++],pch);
		}
	}
	//printf("\n");
	tache.nbParam=ptrParam;
	for (int i = 0 ; i < ptrParam ; i++ ){
		printf("parametre %d : %s\n",i,tache.parametres[i]);
	}
}