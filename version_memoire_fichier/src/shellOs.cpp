//
//  shellOS.cpp
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
    FILE *testFic = fopen(filename,"r");
    if (testFic == NULL){
		std::cout << "ERROR : memory file not initialized ; run os process first\n";
		exit (-1);
	}
    maMemoire.init(filename);
	//std::cout << "maMemoire initialized \n";
	mesTaches.init(filename);
	//std::cout << "mesTaches initialized \n";
	if (argv[1] != NULL){
		strcpy(userName, argv[1]);
	}else{
	    printf("Saisissez un nom d'utilisateur : ");
	    gets(userName);
	}
	
    int id = monUser.getNewUserId();
    int userBlocId = maMemoire.alloueBloc(100, BLOC_TYPE_USR, userName, id);
    monUser.init(filename, id, userName);
    monUser.setName(userName);

    Console::Console();
    maMemoire.libereBloc(userBlocId);
    return 0;
}
