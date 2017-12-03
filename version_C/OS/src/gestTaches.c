
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/tache.h"


int ptrLastTache=0;
int taskId=1;

char cmdHistory[HISTORY_SIZE][BUFF_SIZE];
int ptrHistory=0;
int courantPriorityLevel=PRIO_INIT;

/*****************************
*
*      execTache
*
******************************/
int execTache(taskStruct tache){
	void (*ptrLancement)(void);
	ptrLancement = tache.tContext.ptrFonction;
	(*ptrLancement)();
	printf("%s a ete lancé", tache.name);
	return 0;
}

/*****************************
*
*      killTache
*
******************************/
void killTache(char *str){
	int pid=atoi(str);
	if (pid == 0){
		printf("argument invalide %s\n", str);
		return;
	}
	int i;
	for (i=0 ; i < SIZE_TBL_TASK ; i ++){
		if ( pid == tblTache[i].pid){
			//printf("Kill de la tache %d (%s)\n",pid, tblTache[i].name);
			tblTache[i].state = TASK_FINIE;
			return;
		}
	}
}

/*****************************
*
*      createTache
*
******************************/
void createTache(char *commande, int priority, void *ptrFonction){
	//printf("[createTache] commande recue : %s\n",commande);
	// on teste si c'est une commande interne
	if (isCommandeInterne(commande)){
		execCommandeInterne(commande);
		return;
	}
	taskStruct newTache;
	strcpy(newTache.commande,commande);
	//printf("[createTache] sauvegarde de la commande dans la structure : %s\n",commande);
	char *pch = strtok (commande, " ");
	strcpy(newTache.name, pch);
	newTache.tContext.ptrFonction=ptrFonction;
	newTache.initialPriority=priority;
	newTache.priority=priority;
	newTache.state=TASK_ACTIVE;
	newTache.pid=taskId;
	tblTache[ptrLastTache]=newTache;
	ptrLastTache++;
	//printf("createTache : %s a ete ajouté a la liste d'execution (id=%d)\n",newTache.name,taskId);
	taskId++;
	// on enregistre la commande dans l'historique
	//printf("createTache : on enregistre la commande %s en position %d\n", commande, ptrHistory);
	strcpy(cmdHistory[ptrHistory++],newTache.commande);
	if (ptrHistory >= HISTORY_SIZE){
		ptrHistory=0;
	}
}


/*****************************
*
*      affNbTaches
*
******************************/
void affNbTaches(){
	int i;
	int nbAct=0;
	int nbSom=0;
	int nbFin=0;
	for (i=0 ; i < SIZE_TBL_TASK ; i ++){
		switch(tblTache[i].state){
			case TASK_ACTIVE:
				nbAct++;
				break;
			case TASK_SOMMEIL:
				nbSom++;
				break;
			case TASK_FINIE:
				nbFin++;
				break;
		}
	}
	printf("nb Taches : actives(%d); sommeil(%d); finie(%d)\n",nbAct,nbSom,nbFin);
	listTaches();
}

/*****************************
*
*      affHistory
*
******************************/
void affHistory(){
	int i;
	int pos;
	for (i=0 ; i < HISTORY_SIZE ; i ++){
		pos = (ptrHistory + i) % HISTORY_SIZE;
		printf("%d : %s\n",(HISTORY_SIZE - i), cmdHistory[pos]);
	}
}

/*****************************
*
*      listTaches
*
******************************/
void listTaches(void){
	int i;
	printf("+------+---------------+------+-------+--------------------------+\n");
	printf("|  ID  |      Nom      | prio | state |  Commande                |\n");
	printf("+------+---------------+------+-------+--------------------------+\n");
	for (i=0 ; i < SIZE_TBL_TASK ; i ++){
		if (tblTache[i].state == TASK_ACTIVE || tblTache[i].state == TASK_SOMMEIL){
			printf("| %4d |",tblTache[i].pid);
			printf(" %-13s |",tblTache[i].name);
			printf("  %3d |",tblTache[i].priority);
			switch (tblTache[i].state){
				case TASK_ACTIVE :
					printf("  ACT  |");
					break;;
				case TASK_SOMMEIL :
					printf("  SLP  |");
					break;;
				case TASK_FINIE :
					printf("  OUT  |");
					break;;

			}
			printf(" %-24s |",tblTache[i].commande);
			printf("\n");
		}
	}
	printf("+------+---------------+------+-------+--------------------------+\n");
}

/*****************************
*
*      lsTaches
*
******************************/
void lsTaches(void){
	system("ls taches/");
}
