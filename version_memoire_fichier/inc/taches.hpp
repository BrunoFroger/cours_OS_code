//
//  taches.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//



#include <iostream>
#include <fstream>
#include "memoire.hpp"

#ifndef taches_hpp
#define taches_hpp

#define NB_PARAMS	10
#define MAX_TACHES	100

#define TASK_ACTIVE	1
#define TASK_SLEEP 	2
#define	TASK_KILLED	3
#define TASK_NA		-1

typedef struct {
	char name[50];
	int owner;
	int father;
	int taskId;
	int status;
	int priority;
}structTache;

class Taches{
private:
	char filename[50];
	int owner;
	char type[5];
	char buffer[MAX_BUFFER];
	FILE * memoryFile;
	int tailleStructBloc;
	void openMemoryFile(void);
	structTache tblTaches[MAX_TACHES];

public:
	Taches(void);
	void init(char *nom);
	int lance(char *chaine);
	void listeTaches(void);
	int kill(char *chaine);
	int kill(int id);
	structTache getNextActiveTask(int priorityLevel);
	void pushActiveTask(structTache tache);
	void creeBlocTache(char *chaine, long taille, char *texte);

};

#endif
