//
//  os.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <unistd.h>

#include "../inc/memoire.hpp"
#include "../inc/console.hpp"

using namespace std;

MemPartagee memPartagee;
structMemPartagee *maStructMemPartagee;
char nomMemoirePartagee[50];
BlocMemoire *fisrtBlockMemoire;

int main(int argc, const char * argv[]) {
    std::cout << "Simulateur d'OS\n";

    maStructMemPartagee = (structMemPartagee *) malloc(sizeof(structMemPartagee));
    strcpy(nomMemoirePartagee,"MemPartagéé : OS");

    memPartagee.initMemPartagee(maStructMemPartagee, nomMemoirePartagee, fisrtBlockMemoire);
    std::cout << "memoire partagee initialisee\n";


    Memoire maMemoire;
    std::cout << "memoire initialisee\n";

    memPartagee.affiche();
    
    Console::Console();   

    std::cout << "fin du process OS \n";

    return 0;
}
