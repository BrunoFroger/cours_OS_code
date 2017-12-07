//
//  memPartagee.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include "../inc/memoire.hpp"
#include "../inc/os.hpp"

#ifndef memPartagee_hpp
#define memPartagee_hpp

// definition de la memoire partagée
#define CLEF	124365
typedef struct
{
	char nomMemPartagee[50];
	BlocMemoire *firstBlocMemoire;
	
}structMemPartagee;



class MemPartagee{
private:
	int memId;
	structMemPartagee *ptrMemPartagee;
	void affErrno();
public:
	MemPartagee(void);
	void initMemPartagee(structMemPartagee *maStructMemPartagee, char * nom, BlocMemoire *fisrtBlocMemoire);
	void getMemPartagee(structMemPartagee *maStructMemPartagee);
	void setFirstBlocMemoire(BlocMemoire *bloc);
	BlocMemoire *getFirstBlocMemoire(void);
	void setNom(char *nom);
	char *getNom(void);
	void affiche(void);
	void killMemPartagee(structMemPartagee *ptr);
};

#endif

extern structMemPartagee *ptrMemPartagee;
