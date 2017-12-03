
#include <stdio.h>

#include "../inc/tache.h"

/*****************************
*
*      getNextActiveTache
*
******************************/
taskStruct *getNextActiveTache(taskStruct *currentTask){
	int priority=0;
	int ptrTask;
	int i;
	int nbActiveTasks=0;
	int nbSleepingTasks=0;
	//affNbTaches();
	for (i=0 ; i < SIZE_TBL_TASK ; i ++){
		if (currentTask != NULL){
			if (tblTache[i].state == TASK_ACTIVE && tblTache[i].pid == currentTask->pid){
				// on ignore la tache courante
				//printf("on ignore la tache courante\n");
				continue;
			}			
		}
		// on cherche la tache active ayant la priorite la plus haute
		if (tblTache[i].state == TASK_ACTIVE){
			//printf("test d'activation de la tache (%d) active %s, (%d/%d)\n",i, tblTache[i].name, tblTache[i].priority,priority);
			// on cherche la tache active de plus haute priorite
			if (tblTache[i].priority > priority){
				priority = tblTache[i].priority;
				ptrTask = i;
			}			
		}
	}
	if (priority == 0){
		// plus de taches dans la liste des taches actives
		return NULL;
	}
	tblTache[ptrTask].priority=tblTache[ptrTask].initialPriority;
	//printf("[getNextActiveTache] : nb taches = %d; next tache = %s\n",ptrLastTache, tblTache[ptrTask].name);
	return &(tblTache[ptrTask]);
}

/*****************************
*
*      pushActiveTache
*
******************************/
void pushActiveTache(taskStruct *tache){
	ptrLastTache ++;
	tache->state=TASK_ACTIVE;
	tblTache[ptrLastTache] = *tache;
}

/*****************************
*
*      pushSleepingTache
*
******************************/
void pushSleepingTache(taskStruct *tache){
	ptrLastTache ++;
	tache->state=TASK_SOMMEIL;
	tblTache[ptrLastTache] = *tache;
	// TODO on enleve la tache des taches actives
}


/*****************************
*
*      I D L E 
*
******************************/
void idle(void){
	printf("tache Idle\n");
	printf("Appuyer sur une touche\n");
	getchar();
	// todo a definir
}

/*****************************
*
*      S C H E D U L E R 
*
******************************/
void scheduler(void){
	taskStruct *currentTask=NULL;
	taskStruct *newTache=NULL;
	taskStruct *nextTask;
	while (1){
		newTache=getNextActiveTache(currentTask);
		void (*ptrFonction)(void);
		void (*ptrFonctionAvecParam)(taskStruct tache);
		if (newTache != NULL){
			if (currentTask == NULL){
				// on execute la nouvelle tache
				nextTask = newTache;
				nextTask->priority=nextTask->initialPriority;
				//printf("scheduler : 1 : pas de tache courante, on execute la nouvelle tache : %s\n",nextTask->name);
			}else{
				// on verifie si c'est vraiment une nouvelle tache
				if(newTache->pid == currentTask->pid){
				// on continue l'execution de la tache courante
					nextTask = currentTask;
					//printf("scheduler : 2 : pid identiques, on reste avec la tache courante : %s\n",nextTask->name);
				}else{
					// on verifie le niveau de priorite
					if (newTache->priority >= currentTask->priority){
						// on execute la nouvelle tache
						nextTask = newTache;
						//printf("scheduler : 3 : priority : on execute la nouvelle tache : %s\n",nextTask->name);
					}else{
						// on reste sur la tache courante
						nextTask = currentTask;
						currentTask->priority--;
						//printf("scheduler : 4 : priority : on reste avec la tache courante : %s\n",nextTask->name);
					}
				}
			}
		}else {
			// newTache == NULL
			if (currentTask != NULL){
				// on reste sur la tache courante
				nextTask = currentTask;
				//printf("scheduler : 5 : pas de nouvelle tache, on reste avec la tache courante : %s\n",nextTask->name);
			}else{
				// plus aucune tache active
				// on execute la tache idle
				//printf("scheduler : 6 : execution de la tache Idle\n");
				idle();
				break;
			}
		}
		// on execute la tache selectionnée
		//printf("priorite = %d => execution de %s\n",nextTask->priority, nextTask->name);
		ptrFonction=nextTask->tContext.ptrFonction;
		ptrFonctionAvecParam=nextTask->tContext.ptrFonction;
		currentTask = nextTask;
		//if (sizeof(nextTask->parametres[0])!=0){
		//listTaches();
		//printf("[scheduler] : exec tache %s prio (%d)\n",nextTask->name,nextTask->priority);
		(*ptrFonctionAvecParam)(*nextTask);
		//}else{
		//	(*ptrFonction)();				
		//}
	}
}
