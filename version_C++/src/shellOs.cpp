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
structMemPartagee *maStructMemPartagee;
BlocMemoire *fisrtBlockMemoire;

int main(int argc, const char * argv[]) {
    std::cout << "shell OS\n";
    
    maStructMemPartagee = (structMemPartagee *)malloc(sizeof(structMemPartagee));

    memPartagee.getMemPartagee(maStructMemPartagee);
    std::cout << "memoire partagee initialisee\n";

    fisrtBlockMemoire=memPartagee.getFirstBlocMemoire();

    //Console::Console();

    return 0;
}
