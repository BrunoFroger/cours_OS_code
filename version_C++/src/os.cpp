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
BlocMemoire *firstBlocMemoire;

int main(int argc, const char * argv[]) {
    std::cout << "Simulateur d'OS\n";

    maStructMemPartagee = (structMemPartagee *)malloc(sizeof(structMemPartagee));
    strcpy(nomMemoirePartagee,"MemPartagéé OS");
    firstBlocMemoire = (BlocMemoire *)malloc(sizeof(BlocMemoire));
    std::cout << "creation maStructMemPartagee : " << maStructMemPartagee << "\n";
    std::cout << "creation firstBlocMemoire    : " << firstBlocMemoire << "\n";
    std::cout << "creation nomMemoirePartagee  : " << nomMemoirePartagee << "\n";

    memPartagee.initMemPartagee(maStructMemPartagee, nomMemoirePartagee, firstBlocMemoire);
    std::cout << "memoire partagee initialisee\n";

    std::cout << "os : fistBlocMemoire apres init mem partagee : " << firstBlocMemoire << "\n";

    std::cout << "os : initialisation de la memoire\n";
    Memoire maMemoire;
    std::cout << "os : memoire initialisee\n";

    memPartagee.affiche();

    firstBlocMemoire->affBlocs();    
    Console::Console();   

    //std::cout << "fin du process OS \n";

    return 0;
}
