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
	char type[5];
	char name[50];
	int owner;
	int id;
	long size;
	char status[5];
	char *datas;
	char fin[10];
}structBloc;


class Memoire{
private:
	char filename[50];
	char buffer[MAX_BUFFER];
	FILE * memoryFile;
	int tailleStructBloc;
	void dump(long offset, long nb);
	void openMemoryFile(void);

public:
	Memoire();
	void init(char *nom);
	long memWrite(long offset, char *datas);
	char * memRead(long offset, long nb);
	void display(long offset, long nb);
	int alloueBloc(long taille, char *type);
	int alloueBloc(long taille, char *type, char *blocName);
	int alloueBloc(long taille, char *type, char *blocName, int userId);
	int alloueBloc(long taille, char *type, int userId);
	void listeBlocs(void);
	structBloc getBloc(int id);
	structBloc getBloc(char *chaine);
	void afficheBloc(structBloc bloc);
	int nbBlocs(void);
	void libereBloc(int id);
	void kill(void);
	void kill(char *filename);
	long blocWrite(int id, long offset, char *datas);
	char *blocRead(int id, long offset, long nb);
	void garbageCollector(void);
	char *getPtrData(int id);
};



#endif /* memoire_hpp */
