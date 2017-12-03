//
//  console.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include "../inc/memPartagee.hpp"


#ifndef console_hpp
#define console_hpp



//-----------------------------
//
//   class console
//
//-----------------------------
class Console{
private:
	structMemPartagee *ptrMemPartagee;

	void lireChaine(char *chaine, int size);
	void analyseCommande(char *chaine);
	void help(void);
	int isCommandeInterne(char *commande);

public:
	Console(void);				// constructeur
};



#endif