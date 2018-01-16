//
//  test.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>

#include "../inc/Memoire.hpp"
#include "../inc/Console.hpp"
#include "../inc/os.hpp"
#include "../inc/taches.hpp"
#include "../inc/tools.hpp"
#include "../inc/users.hpp"


using namespace std;

Memoire maMemoire;
Taches mesTaches;
Users monUser;

int main(int argc, const char * argv[]) {
    INFO("===================================");
    INFO("OS simulator :   session start     ");
    INFO("-----------------------------------");

    char filename[50];

    strcpy(filename, MEMORY_FILENAME);
    // par securité on detruit le fichier memoire cree
    maMemoire.kill(filename);

    //INFO("creation memoire 0");
	maMemoire.init(filename);
	mesTaches.init(filename);
    maMemoire.alloueBloc(100000, (char *)BLOC_TYPE_MEM);
    char name[20];
    strcpy(name,"root");
    //printf("nom du bloc = %s\n", name);
    maMemoire.alloueBloc(100, (char *)BLOC_TYPE_USR, name, 0);
    monUser.init(filename,0, name);

    int cpt;
    while (1){
        Console::Console();
        cpt = monUser.nbUsers();
        //printf("%d users conectes\n",cpt);
        if (cpt == 1){
            break;
        }else{
            std::cout << "ERROR : impossible to exit : " << (cpt - 1) << " other users are connected\n";
        }
    }

    maMemoire.kill();

    INFO("-----------------------------------");
    INFO("OS simulator :   session end       ");
    INFO("===================================");
    return 0;
}
