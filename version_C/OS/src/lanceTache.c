

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/tache.h"

int file_size(char *filename){
   /*Ouverture du fichier*/
   FILE *file = fopen(filename, "r");
   long ret;
    
   if(file == NULL)
   {
      return -1;
   }
    
   /*On place le curseur à la fin*/
   fseek(file, 0, SEEK_END);
   /*On récupére la position courante*/
   ret = ftell(file);
   fclose(file);
   return ret;
}

void lanceTache(taskStruct tache){
	char commande[BUFF_SIZE];

	// traitement d'une commande externe
	strcpy(commande,tache.commande);
	// decomposition de la commande 
	char *pch = strtok (commande, " ");
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
	char cde[BUFF_SIZE];

	/*strcpy(cde,EXEC_DIR);
	strcat(cde,commande);
	strcat(cde," > /dev/null");
	printf("[lanceTache] : execute tache externe <%s>\n",cde);
	short result = system(cde)>>8;
	if (result == 127){*/
		// on execute une commande shell
	strcpy(cde,commande);
	int fileSize=file_size(cde);
	if (fileSize != -1){
		// on charge le code en memoire
		// allocation d'une zone memoire pour cette tache
	}
	//short result = system(cde)>>8;
	//}
	//printf("[lanceTache] : retour commande <%s> : <%d>\n", cde, result);
	sprintf(cde,"%d",tache.pid);
	killTache(cde);
}