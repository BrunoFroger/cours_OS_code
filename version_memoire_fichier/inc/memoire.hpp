//
//  memoire.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#include <iostream>
#include <fstream>


#ifndef memoire_hpp
#define memoire_hpp

#define BLOC_FREE	"Free"
#define BLOC_USED	"Used"
#define MAX_BUFFER	10000


typedef struct {
	char debut[10];
	char name[50];
	int id;
	long size;
	char status[5];
	void * datas;
	char fin[10];
}structBloc;


class Memoire{
private:
	char filename[50];
	char buffer[MAX_BUFFER];
	FILE * memoryFile;
	int tailleStructBloc;

public:
	Memoire();
	Memoire(char *nom);
	long memWrite(long offset, char *datas);
	char * memRead(long offset, long nb);
	void display(long offset, long nb);
	int alloueBloc(long taille);
	void listeBlocs(void);
	structBloc getBloc(int id);
	void afficheBloc(structBloc bloc);
};



#endif /* memoire_hpp */