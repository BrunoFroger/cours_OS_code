//
//  test.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <cstdio>

#include "../inc/Memoire.hpp"
#include "../inc/Console.hpp"
#include "../inc/os.hpp"
#include "../inc/taches.hpp"
#include "../inc/users.hpp"


using namespace std;

Memoire maMemoire;
Taches mesTaches;
Users monUser;

int main(int argc, const char * argv[]) {
    //std::cout << "Simulateur d'OS : shell externe\n";
    
    char filename[50];
    char userName[50];
    char tmpName[50];

    strcpy(filename, MEMORY_FILENAME);
    maMemoire.init(filename);
	mesTaches.init(filename);
	if (strlen(argv[1]) > 0){
		strcpy(userName, argv[1]);
	}else{
	    printf("Saisissez un nom d'utilisateur : ");
	    gets(userName);
	}
    // trouver un moyen de recuperer le dernier userId utilisé
    int id = monUser.getNewUserId();
    //sprintf(tmpName,"user %s",);
    int userBlocId = maMemoire.alloueBloc(100, BLOC_TYPE_USR, userName, id);
    monUser.init(filename, id, userName);
    monUser.setName(userName);

    Console::Console();
    maMemoire.libereBloc(userBlocId);
    return 0;
}
