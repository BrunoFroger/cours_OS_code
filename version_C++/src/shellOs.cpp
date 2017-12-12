//
//  shellOs.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <unistd.h>

#include "../inc/console.hpp"

using namespace std;

MemPartagee memPartagee;
//structMemPartagee *maStructMemPartagee;
BlocMemoire *firstBlocMemoire;

int main(int argc, const char * argv[]) {
    std::cout << "shell OS\n";

    memPartagee.getMemPartagee();
    std::cout << "memoire partagee initialisee\n";

    //memPartagee.getFirstBlocMemoire();
    //memPartagee.affiche();

    Console::Console();

    return 0;
}
