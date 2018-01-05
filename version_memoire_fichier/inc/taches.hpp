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


class Taches{
private:
	char filename[50];
	int owner;
	char type[5];
	char buffer[MAX_BUFFER];
	FILE * memoryFile;
	int tailleStructBloc;
	void openMemoryFile(void);

public:
	Taches(void);
	void init(char *nom);
	int lance(char *chaine);
	void listeTaches(void);
	int kill(char *chaine);
	int kill(int id);

};

#endif