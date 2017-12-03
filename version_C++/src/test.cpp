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
#include "../inc/memPartagee.hpp"


using namespace std;

MemPartagee memPartagee;
structMemPartagee maStructMemPartagee;

int main(int argc, const char * argv[]) {
    std::cout << "tests Simulateur d'OS\n";
    
    int result;

    // Initialisation de la memoire


    cout << "creation memoire 0\n";
    Memoire maMemoire(100000);
    firstBlocMemoire->affBlocs();


    if(1==1){ // activation des tests de manipulation de la memoire

        if (1 == 1){ // creation d'un 2 eme bloc memoire
            cout << "creation memoire 1\n";
            Memoire maMemoire1(50);
            firstBlocMemoire->affBlocs();
        }

        if (1 == 1){ // creation d'un 3 eme bloc memoire
            cout << "creation memoire 2\n";
            Memoire maMemoire1(10000);
            firstBlocMemoire->affBlocs();
        }
        cout << "memoire globale initialisée\n";

        if (1 == 1){ // test garbage collector sur zone memoire
            cout << "test garbage collector sur zone memoire\n";
            maMemoire.garbageCollector(GC_SIMPLE);
            firstBlocMemoire->affBlocs();
        }


        // creation/modification de blocs
        if (1 == 0){ // test creation de bloc et garbage collector
            BlocMemoire *monBloc1=maMemoire.alloue((char *)"bloc1",10);
            if (monBloc1 == NULL) return KO;
            BlocMemoire *monBloc2=maMemoire.alloue((char *)"bloc2",100);
            if (monBloc2 == NULL) return KO;
            BlocMemoire *monBloc3=maMemoire.alloue((char *)"bloc3",20);
            if (monBloc3 == NULL) return KO;

            firstBlocMemoire->affBlocs();
            monBloc2->freeBloc();
            firstBlocMemoire->affBlocs();

            BlocMemoire *monBloc4=maMemoire.alloue((char *)"bloc4",20);
            if (monBloc4 == NULL) return KO;
            BlocMemoire *monBloc5=maMemoire.alloue((char *)"bloc5",20);
            if (monBloc5 == NULL) return KO;
            BlocMemoire *monBloc6=maMemoire.alloue((char *)"bloc6",30);
            if (monBloc6 == NULL) return KO;

            cout << "display info of bloc6\n";
            monBloc6->affBlocDetail();

            firstBlocMemoire->affBlocs();
            monBloc5->freeBloc();
            monBloc6->freeBloc();
            firstBlocMemoire->affBlocs();

            cout << "garbage collector simple\n";
            maMemoire.garbageCollector(GC_SIMPLE);

            firstBlocMemoire->affBlocs();

            cout << "display info of bloc6\n";
            if(monBloc6 != NULL){
                monBloc6->affBlocDetail();
            }else{
                cout << "bloc6 n'existe plus\n";
            }

            char chaine[20]="essai12345";
            void *tmp;
            tmp = (void *)chaine;
            printf("essai de remplissage avec %s du bloc memoire %s \n", (char*)tmp, monBloc1->getName());
            result = monBloc1->fill(0,tmp,(long)strlen(chaine));
            if (result == KO) return KO;
            printf("essai de remplissage avec %s du bloc memoire %s \n", (char*)tmp, monBloc5->getName());
            monBloc5->fill(10,tmp,(long)strlen(chaine));
            maMemoire.dump(0,100);        
        }
    }

    return 0;
}
