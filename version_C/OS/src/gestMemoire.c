

#include <stdio.h>
#include <string.h>

#include "../inc/mem.h"



char memoire[MEM_SIZE];
memStruct tblPtrMem[SIZE_TBL_MEM];


void freeBlocMem(int i){
	int debut = tblPtrMem[i].ptrZone;
	int taille = tblPtrMem[i].size;
	int index;

	if (debut != -1){		
		// on met des espaces dans toute la zone meoire reservée
		for (index = 0 ; i < taille ; i++){
			memoire[index+taille] = ' ';
		}
	}
	// liberation de la memoire associée

	freeMem(tblPtrMem[i].ptrZone,tblPtrMem[i].size);
	tblPtrMem[i].ptrZone=-1;
	tblPtrMem[i].size=-1;
	tblPtrMem[i].status=MEM_STATUS_FREE;
	tblPtrMem[i].pid=-1;
}

void initMem(){
	//printf("initialisation de la memoire\n");
	for (int i=0 ;  i < SIZE_TBL_MEM ; i++){
		//printf(".");
		freeBlocMem(i);
	}
	//printf("\n");
}

void garbageCollector(int mode){
	printf("garbage collector\n\n");
	switch (mode){
		case GC_MODE_SIMPLE:
			printf("GC simple\n");
			printf("a realiser .....\n");
			break;
		case GC_MODE_FULL:
			printf("GC full\n");
			printf("a realiser .....\n");
			break;
		default:
			printf("mode GC inconnu %d\n",mode);
			break;
	}
}


void freeMem(int ptrMem, int size){
	// si le pointeur est a -1, c'est que c'est une zone deja libre
	if (ptrMem == -1){
		return;
	}
	// si la taille est a -1 on a rien a faire sauf remettre a -1 le ptrMem
	if (size == -1){
		ptrMem = -1;
		return;
	}
	// on recherche le bloc commancant a l'adresse ptrMem.ptrzone
	for (int i = ptrMem ; i < size ; i++){
		memoire[i] = 0;
	}
	return;
}

memStruct * allocMem(int size){
	printf("fonction allocation d'un bloc memoire\n\n");
	memStruct *ptr;

	printf("a realiser .....\n");
	return ptr;
}

memStruct * reAllocMem(memStruct * ptrMem, int newSize){
	printf("fonction changement de la taille d'un bloc memoire\n\n");
	memStruct *ptr;

	printf("a realiser .....\n");
	return ptr;
}

void memUsage(int mode){
	int i,zone,size,status,pid;
	char statusDisp[6];
	int nbFree=0;
	int nbUsed=0;
	int nbOther=0;
	// affichage de l'entete
	printf("+----+----------+-------+--------+------+\n");
	printf("| N° | Ptr Zone |taille | status | pid  |\n");
	printf("+----+----------+-------+--------+------+\n");
	for (i = 0 ; i < SIZE_TBL_MEM ; i++){
		zone=tblPtrMem[i].ptrZone;
		size=tblPtrMem[i].size;
		status=tblPtrMem[i].status;
		pid=tblPtrMem[i].pid;
		switch (status){
			case MEM_STATUS_FREE:
				strcpy(statusDisp,"FREE");
				nbFree++;
				break;
			case MEM_STATUS_USED:
				strcpy(statusDisp,"USED");
				nbUsed++;
				break;
			default:
				strcpy(statusDisp,"N/A");
				nbOther++;
				break;
		}
		if (mode == status){
			printf("| %2d |    %4d  |  %4d | %6s | %4d |\n",i, zone, size, statusDisp, pid);
		}
	}
	printf("+----+----------+-------+--------+------+\n");
}


void dumpMem(int debut, int taille){
	int i=0;
	int nbItem=16;
	int cpt=0;
	int j=0;
	char car;
	char tblCar[16];

	//printf("Dump memoire de %d à %d", debut, debut+taille);
	printf("%4d :",i);
	for (i=0 ; i < taille ; i ++){
		if (cpt >= nbItem){
			// on affiche les caracteres imprimables
			printf("\t");
			for (j=0 ; j < nbItem ; j++){
				car = tblCar[j];
				if (car >= 0x20 && car <= 0x7e){
					printf("%c",car);
				}else{
					printf(".");
				}
			}
			j=0;
			// on affiche le debut de la nouvelle ligne
			printf("\n%4d :",i);
			if (cpt >= nbItem){
				cpt = 0;
			}
		}
		cpt++;
		if (debut + i >= MEM_SIZE){
			printf("\nle pointeur depasse la valeur max");
			return;
		}
		printf(" %02x", memoire[debut + i]);
		tblCar[j++]=memoire[debut + i];
	}
	// On complete la fin de ligne avant les caracteres imprimante
	int debut1 = debut + i;
	int fin = debut1 - j + 16;
	for (int k = debut1 ; k < fin ; k++){
		printf("   ");
	}
	// on affiche les caracteres imprimable de la derniere ligne incomplete
	int first = debut + i - j;
	int last = first + j;
	printf("\t");
	for (i = first ; i < last ; i++){
		car = memoire[i];
		if (car >= 0x20 && car <= 0x7e){
			printf("%c",car);
		}else{
			printf(".");
		}
	}
	printf("\n");
	//printf("complements de blancs : debut=%d, fin=%d\n",debut1, fin);
	//printf("carcat imprimables first=%d, last=%d\n",first, last);
}

void fillMem(int debut, int size, char car){
	//printf("fillMem : debut=%d, size=%d, car=%c\n",debut, size, car);
	for (int i = debut ; i < debut + size ; i++){
		memoire[i]=car;
	}
}


void storeMem(int debut, char *texte){
	int size = strlen(texte);
	int cpt=0;
	//printf("storeMem : ptr=%d, texte=%s, size=%d\n",debut,texte,size);
	for (int i = debut ; i < debut + size ; i++){
		memoire[i]=texte[cpt++];
	}
}

