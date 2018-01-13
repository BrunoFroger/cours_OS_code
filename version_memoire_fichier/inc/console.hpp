//
//  console.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#ifndef console_hpp
#define console_hpp

//-----------------------------
//
//   class console
//
//-----------------------------
class Console{
private:
	void lireChaine(char *chaine, int size);
	int analyseCommande(char *chaine);
	void help(void);
	int isCommandeInterne(char *commande);
	void historiseCommande(char *commande);

public:
	Console(void);				// constructeur
	static char * getParam(char *chaine, int idx);
	void AffHistoryCommandes(void);
};

#endif
