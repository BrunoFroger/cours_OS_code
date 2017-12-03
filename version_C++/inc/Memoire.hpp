//
//  memoire.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#ifndef memoire_hpp
#define memoire_hpp

#include <stdio.h>

#define MEMORY_SIZE     100000
#define MEM_STATUS_FREE	1
#define MEM_STATUS_USED	2

#define GC_FULL		1
#define GC_SIMPLE	2	// regroupe les blocs libres

//-----------------------------
//
//   class BlocMemoire
//
//-----------------------------
class BlocMemoire{
private:
	char name[20];							// nom du bloc
	long size;								// taille du bloc
	long ptr;								// offset dans stockage
	int status;								// FREE or USED
	BlocMemoire *nextBloc;					// ptr sur bloc suivant
	char *stockage;							// lien vers la memoire physique
	int idStockage;							// id de la zone de stockage
public:
	BlocMemoire(void);						// constructeur
	void init(char *memory, int id, char *nom, long debut, long taille);		// remplis la zone avec des 0
	void affBlocs(void);					// affiche tableau liste des blocs
	void affBlocDetail(void);				// affichage texte du detail d'un bloc
	long getSize(void);						// taille d'un bloc
	long getPtr(void);						// position en memoire du bloc
	int getStatus(void);					// FREE or USED
	char *getName(void);					// nom du bloc
	BlocMemoire *getNextBloc(void);			// pointeur vers bloc suivant
	BlocMemoire *getSubBloc(char *memory, char *name, BlocMemoire *precedent, long taille); // extrait sous bloc d'un bloc libre 
	int nbBlocs(void);						// nombre de blocs utilisés
	void freeBloc(void);					// change status du bloc
	int concatBlocs(void);					// concatene le bloc courant avec son suivant
	int fill(long offset, void *data, long dataSize);			// remplissage de la memoire
	void libere(void);						// libere memoire du bloc
	int link(BlocMemoire *bloc);			// init lien blocSuivant de bloc avec ce bloc
	int getIdStockage(void);				// id de zone memoire
};

//-----------------------------
//
//   class Memoire
//
//-----------------------------
class Memoire{
private:
    char *memoireOS;
	//void initMem(long taille);					// initialise toute la zone memoire

public:
	Memoire();									// constructeur par defaut
	Memoire(long taille);						// constructeur
	BlocMemoire *alloue(char *name, long taille);			// crée un bloc et alloue un zone memoire 
	void dump(long debut, long taille);			// dump hexa/scii de la memoire
	void garbageCollector(int mode);			// nettoyage de la memoire et des blocs
};


extern BlocMemoire *firstBlocMemoire;			// point d'entree des blocs meomire

#endif /* memoire_hpp */
