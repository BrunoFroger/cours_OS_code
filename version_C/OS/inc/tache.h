




#ifndef _TASK_H
#define _TASK_H

// definition des differents etarts de taches
#define TASK_ACTIVE 1
#define TASK_SOMMEIL 2
#define TASK_FINIE 0
#define SIZE_TBL_TASK 20
#define PRIO_INIT 128
#define HISTORY_SIZE 25
#define BUFF_SIZE 50
#define MAX_PARAM 5
#define EXEC_DIR "taches/"


typedef struct {
	void * ptrFonction;
	int size;
	int ptrDebutCode;
	int codeSize;
	int ptrDebutVariables;
	int variableSize;
	int ptrDebutTas;
	int tasSize;
	int ptrExec;
}taskContext;

typedef struct {
	int pid;
	char name[BUFF_SIZE];
	char commande[BUFF_SIZE];
	char parametres[MAX_PARAM][BUFF_SIZE];
	int nbParam;
	int priority;
	int initialPriority;
	int user;
	int state; 		// active, Sommeil, finie 
	taskContext tContext;
}taskStruct;

taskStruct tblTache[SIZE_TBL_TASK];

#endif



extern int ptrLastTache;
extern int ptrHistory;
extern char cmdHistory[HISTORY_SIZE][BUFF_SIZE];
extern int courantPriorityLevel;



extern void monitor(void);
extern void scheduler(void);
//extern void emulateur(int nbParam, char parametres[MAX_PARAM][BUFF_SIZE]);
extern void lanceTache(taskStruct tache);
extern void killTache(char *str);
extern void createTache(char *commande, int priority, void *ptrFonction);
extern int execTache(taskStruct tache);
extern void listTaches(void);
extern void lsTaches(void);
extern void shell(char *commande);
extern void affNbTaches(void);
extern void affHistory();
extern int isCommandeInterne(char *commande);
extern void execCommandeInterne(char *commande);

