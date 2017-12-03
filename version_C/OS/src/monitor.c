

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/tache.h"

char prompt[BUFF_SIZE]="Cours OS > ";
char recallCommand[BUFF_SIZE]="";
char commande[BUFF_SIZE];

/*****************************
*
*      lireChaine
*
******************************/
void lireChaine(char chaine[], int size) {
	fgets(chaine, size, stdin);
	chaine[strlen(chaine) - 1] = '\0';
}

/*****************************
*
*      execCommande
*
******************************/
void execCommande(char *commande, int priority){
	char car=commande[0];
	char car1=commande[1];
	char car2=commande[2];
	strcpy(recallCommand,"");
	// test si la commande est du texte ou une fleche
	if (car == 27 && car1 == 91){   // ESC
		switch (car2){
			case 65 : // fleche haut
				// on cherche commande precedente dans l'historique des commandes
				//printf("[monitor] : fleche haut\n");
				ptrHistory--;
				if (ptrHistory < 0){
					ptrHistory = HISTORY_SIZE - 1;
				}
				break;
			case 66 : // fleche bas
				// on cherche commande suivante dans l'historique des commandes
				//printf("[monitor] : fleche bas\n");
				ptrHistory++;
				if (ptrHistory >= HISTORY_SIZE){
					ptrHistory = 0;
				}
				break;
			default:
				printf("[monitor] : Caracteres interdits (%d, %d, %d)\n",car, car1, car2);
				return;
				break;
		}
		strcpy(recallCommand,cmdHistory[ptrHistory]);
		return;
	}
	// mise en file d'attente de la nouvelle tache
	/*printf("on enregistre la commande %s en position %d", commande, ptrHistory);
	strcpy(cmdHistory[ptrHistory++],commande);
	if(ptrHistory >= HISTORY_SIZE){
		ptrHistory=0;
	}*/
	createTache(commande, priority, lanceTache);
}

/*****************************
*
*      monitor
*
******************************/
void monitor(void){
	strcpy(commande,"");
	printf("%s%s", prompt, recallCommand);
	if (strcmp(recallCommand,"") == 0){
		lireChaine(commande,BUFF_SIZE);
	}else{
		strcpy(commande,recallCommand);
	}
	if (strlen(commande) != 0){
		execCommande(commande,courantPriorityLevel);
	}
}