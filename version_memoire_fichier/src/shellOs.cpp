//
//  test.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>

#include "../inc/Memoire.hpp"


using namespace std;

int main(int argc, const char * argv[]) {
    std::cout << "Simulateur d'OS : shell externe\n";
    
    char filename[50];

    strcpy(filename, "memoire1.dta");
    cout << "creation memoire 0\n";
    Memoire maMemoire(filename);

    return 0;
}
