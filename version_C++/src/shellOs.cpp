//
//  shellOs.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>

#include "../inc/console.hpp"

using namespace std;

MemPartagee memPartagee;
structMemPartagee *maStructMemPartagee;
char nomMemoirePartagee[50];
BlocMemoire *fisrtBlockMemoire;

int main(int argc, const char * argv[]) {
    std::cout << "shell OS\n";


    maStructMemPartagee = (structMemPartagee *) malloc(sizeof(structMemPartagee));
    strcpy(nomMemoirePartagee,"MemPartagéé : shell shellOs");

    maStructMemPartagee = memPartagee.getMemPartagee();
    std::cout << "memoire partagee initialisee\n";
    memPartagee.affiche();

    fisrtBlockMemoire=memPartagee.getFirstBlocMemoire();
    strcpy(nomMemoirePartagee,memPartagee.getNom());

    Console::Console();

    return 0;
}
