

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/tache.h"


void shell(char *commande){
	char cde[BUFF_SIZE];

	strcpy(cde,commande);
	char *pch = strtok (cde, " ");
	pch = strtok(NULL," ");
	printf("Lancement d'une fenetre externe avec monitor avec en parametre la commande <%s>\n",pch);
	if (pch != NULL){
		printf("Lancement avec parametres : <%s>\n", pch);
		sprintf(cde,"xterm -e bin/os %s &",pch);
	}else{
		printf("Lancement sans parametres\n");
		sprintf(cde,"xterm -e bin/os &");

	}
	system (cde);
}