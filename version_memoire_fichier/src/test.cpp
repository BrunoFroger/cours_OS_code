//
//  test.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>

#include "../inc/Memoire.hpp"
#include "../inc/os.hpp"
#include "../inc/taches.hpp"


using namespace std;

Memoire maMemoire;
Taches mesTaches;

int main(int argc, const char * argv[]) {
    std::cout << "Simulateur d'OS : programme de tests\n";
    
    char filename[50];
    long taille;
	    int id;

    strcpy(filename, MEMORY_FILENAME);
    cout << "test : creation memoire 0\n";
    maMemoire.init(filename);
	mesTaches.init(filename);

    if ( 1 == 0 ) {
	    char data[100];
	    strcpy(data,"test data");
	    cout << "test : ecriture de données dans la memoire : " << data << " (" << strlen(data) << ")\n";
	    taille = maMemoire.memWrite(0,data);
	    cout << "test : affichage de données lus dans la memoire taille = " << taille << "\n";
	    //maMemoire.display(0, taille);
	    cout << "\n";    	
    }

    if ( 1 == 1 ){
	    taille=100;
	    cout << "test : allocation d'un bloc de taille : " << taille << "\n";
	    id = maMemoire.alloueBloc(taille, BLOC_TYPE_MEM);
	    cout << "test : bloc avec id = " << id << " alloue\n";

    }
    if ( 1 == 1 ){
	    taille=50;
	    cout << "test : allocation d'un bloc de taille : " << taille << "\n";
	    id = maMemoire.alloueBloc(taille, BLOC_TYPE_MEM);
	    cout << "test : bloc avec id = " << id << " alloue\n";

    }
    if ( 1 == 1 ){
	    taille=200;
	    cout << "test : allocation d'un bloc de taille : " << taille << "\n";
	    id = maMemoire.alloueBloc(taille, BLOC_TYPE_MEM);
	    cout << "test : bloc avec id = " << id << " alloue\n";

    }


    structBloc tmp = maMemoire.getBloc(3);
    maMemoire.afficheBloc(tmp);

	//maMemoire.display(0,400);
	maMemoire.listeBlocs();
    return 0;
}
