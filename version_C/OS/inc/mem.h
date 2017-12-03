


#ifndef __MEM_H
#define __MEM_H


#define MEM_SIZE		100000
#define SIZE_TBL_MEM 	100

#define MEM_STATUS_ALL	0
#define MEM_STATUS_FREE 1
#define MEM_STATUS_USED 2

#define GC_MODE_FULL	1
#define GC_MODE_SIMPLE	2

typedef struct{
	int ptrZone;			// pointeur sur le debut de la zone dans la memoire
	int size;				// taille de la zone
	int status;				// FREE or USED
	int pid;				// pid de la tache utilisant cette zone
} memStruct;



#endif

extern char memoire[MEM_SIZE];
extern memStruct tblPtrMem[SIZE_TBL_MEM];

extern void initMem();						// initialisation de la memoire
extern void garbageCollector(int mode);			// nettoyage de la table de gestion de memoire
extern void freeMem(int ptrMem, int size);
extern memStruct *allocMem(int size);
extern memStruct *reAllocMem(memStruct * ptrMem, int newSize);
extern void memUsage(int mode);
extern void dumpMem(int debut, int taille);
extern void fillMem(int debut, int taille, char );
extern void storeMem(int debut, char *texte);
