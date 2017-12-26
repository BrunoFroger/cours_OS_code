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


using namespace std;

Memoire maMemoire;
Taches mesTaches;

int main(int argc, const char * argv[]) {
    std::cout << "Simulateur d'OS : shell externe\n";
    
    char filename[50];

    strcpy(filename, MEMORY_FILENAME);
    cout << "creation memoire 0\n";
    maMemoire.init(filename);
	mesTaches.init(filename);

    Console::Console();
    return 0;
}
