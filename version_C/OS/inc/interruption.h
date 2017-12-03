
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/tache.h"
#include "../inc/mem.h"

#define PARAM_SIZE	20
#define PARAM_NB	5

char params[PARAM_NB][PARAM_SIZE];
char *lstCommandeInterne[]={"tsk", "kill", "mem", "dumpMem", "fillMem", "hist", "shell", "garbage", "?", "exit"};

void help(void){
	printf("+----------------------------------------------------------------+\n");
	printf("| Liste des commandes internes disponibles                       |\n");	
	printf("+-------------------+--------------------------------------------+\n");
	printf("| tsk               | liste des taches                           |\n");
	printf("| kill <id>         | tue la tache <id>                          |\n");
	printf("| mem  <1|2>        | description de la memoire (1:free, 2:used) |\n");
	printf("| dumpMem  deb n    | dump de n elements de memoire depuis deb   |\n");
	printf("| fillMem deb n car | remplis memoire avec n car depuis deb      |\n");
	printf("| storeMem deb text | remplis memoire avec text depuis deb       |\n");
	printf("| hist              | historique des commandes                   |\n");
	printf("| ls                | liste des taches externes                  |\n");
	printf("| shell             | lance un shell dans une nouvelle fenetre   |\n");
	printf("| garbage           | nettoyage de la memoire                    |\n");
	printf("| ?                 | cette ecran d'aide                         |\n");
	printf("| exit              | quitte OS                                  |\n");
	printf("+-------------------+--------------------------------------------+\n");
}

int isCommandeInterne(char *commande){
	char tmpCommande[BUFF_SIZE];
	strcpy (tmpCommande,commande);
	//printf("[isCommandeInterne] : <%s>\n",commande);
	int nbCmdInterne = sizeof(lstCommandeInterne) / 8;
	for (int i = 0 ; i < nbCmdInterne ; i++){
		// TODO si parametres dans la commande extraire le premier mot
		char *p=strtok(tmpCommande, " ");
		if (strcmp(lstCommandeInterne[i],p) == 0){
			return 1;
		}
	}
	return 0;
}

void execCommandeInterne(char *commande){
	//printf("execCommandeInterne <%s>\n",commande);
	//return;
	char tmpCommande[BUFF_SIZE];
	int nb_param=0;
	char *p;

	strcpy(tmpCommande,commande);
	p=strtok(commande, " ");
	while (p != NULL){
		strcpy(params[nb_param],p);
		//printf("param %d=%s\n",nb_param,params[nb_param]);
		nb_param++;
		if (nb_param >= PARAM_NB){
			printf("trop de parametres (limité a 5) !\n");
			return;
		}
		p = strtok(NULL, " ");
	}
	strcpy(params[nb_param],"");
	if (strcmp(params[0], "tsk") == 0){
		listTaches();
	}else if (strcmp(params[0], "kill") == 0){
		killTache(params[1]);
	}else if (strcmp(params[0], "mem") == 0){
		int mode = atoi(params[1]);
		memUsage(mode);
	}else if (strcmp(params[0], "dumpMem") == 0){
		int debut = atoi(params[1]);
		int taille = atoi(params[2]);
		dumpMem(debut,taille);
	}else if (strcmp(params[0], "fillMem") == 0){
		int debut = atoi(params[1]);
		int taille = atoi(params[2]);
		char car = params[3][0];
		fillMem(debut,taille,car);
	}else if (strcmp(params[0], "storeMem") == 0){
		int debut = atoi(params[1]);
		storeMem(debut,params[2]);
	}else if (strcmp(params[0], "exit") == 0){
		exit(0);	
	}else if (strcmp(params[0], "hist") == 0){
		affHistory();
	}else if (strcmp(params[0], "shell") == 0){
		shell(tmpCommande);
	}else if (strcmp(params[0], "garbage") == 0){
		int mode = atoi(params[1]);
		garbageCollector(mode);
	}else if (strcmp(params[0], "?") == 0){
		help();
	}else{
		printf("commande interne inconnue !\n");
	}
}