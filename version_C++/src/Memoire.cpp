//
//  Memoire.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#include <iostream>

#include "../inc/Memoire.hpp"
#include "../inc/memPartagee.hpp"
#include "../inc/os.hpp"

using namespace std;

char memoryArea[MEMORY_SIZE];
int cptUnusedMemory=0;
char nomTasMemoire[15];

extern MemPartagee memPartagee;
extern structMemPartagee maStructMemPartagee;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Memoire::Memoire(){
    Memoire(MEMORY_SIZE);
}
    
Memoire::Memoire(long taille){
    std::cout << "\n\nMemoire : constructeur : taille = " << taille << "\n";
    long i;
    for (i = 0 ; i < taille ; i++){
        memoryArea[i]=0;
    }
    // on initialise toute la zone memoire a libre en tant qu'un seul bloc
    sprintf(nomTasMemoire, "unused memory %d", cptUnusedMemory);
    std::cout << "Memoire : creation du tas : " << nomTasMemoire << "\n";
    
    BlocMemoire *tmp, *newBloc, *precedent;
    precedent=NULL;
    tmp = firstBlocMemoire;
    // on verifie s'il y a d'autres blocs de memoire crées
    if (tmp != NULL){
        std::cout << "Memoire : au moins 1 bloc existe\n";
        do{
            precedent=tmp;
            if (tmp->getNextBloc() != NULL){
                std::cout << "Memoire : il y a des sous bloc, on passe au suivant \n";
                tmp=tmp->getNextBloc();
            }
        } while (tmp->getNextBloc() != NULL);

    }
    std::cout << "creation d'un nouveau bloc\n";
    newBloc = (BlocMemoire *) malloc(sizeof(BlocMemoire));
    std::cout << "Memoire : initialisation du nouveau bloc : " << newBloc << "\n";
    newBloc->init(memoryArea, cptUnusedMemory, nomTasMemoire, 0, taille);
    if (precedent != NULL){
        std::cout << "Memoire : il y a un bloc precedent, creation du lien \n";
        tmp->link(newBloc);
    }else{
        firstBlocMemoire=newBloc;
        std::cout << "Memoire : c'est le premier bloc, on init fistBlocMemoire : " << firstBlocMemoire << "\n";
        memPartagee.setFirstBlocMemoire(firstBlocMemoire);
        std::cout << "Memoire : c'est le premier bloc, init fistBlocMemoire fait : " << memPartagee.getFirstBlocMemoire() << "\n";
    }
    //firstBlocMemoire->affBlocDetail();
    cptUnusedMemory++;
    memPartagee.setFirstBlocMemoire(firstBlocMemoire);
    std::cout << "Memoire : fin constructeur\n\n";
}

//--------------------------------
//
//     alloue
//
//--------------------------------
BlocMemoire *Memoire::alloue(char *name, long taille){
    //std::cout << "\nMemoire : allocation d'un bloc memoire de taille " << taille << "\n";
    // recherche d'un bloc correspondant a la taille cherchee
    BlocMemoire *bloc = firstBlocMemoire;
    BlocMemoire *blocPrecedent = NULL;
    while (1){
        if (bloc->getStatus() == MEM_STATUS_FREE){
            // ce bloc est libre on peut l'analyser
            if (taille > bloc->getSize()){
                // la taille demandée est superieur a la taille disponible
                // on cherche le bloc suivant
                if (bloc->getNextBloc() == NULL){
                    // plus de bocs disponibles
                    std::cout << "ERROR : no more free bloc found\n";
                    return NULL;
                }else{
                    // on cherche le bloc suivant
                    blocPrecedent=bloc;
                    bloc = bloc->getNextBloc();
                }
            }else{
                // le bloc est valide, on construit le nouveau bloc et on update le chainage
                BlocMemoire *newBloc = bloc->getSubBloc(this->memoireOS, name, blocPrecedent, taille);
                return newBloc;
            }
        }else{
            if (bloc->getNextBloc() != NULL){
                // on verifie avec le bloc suivant
                blocPrecedent=bloc;
                bloc = bloc->getNextBloc();
            }else{
                // plus de bocs disponibles
                std::cout << "ERROR : no more free bloc found\n";
                return NULL;
            }
        }
    }

    return NULL;
}

//--------------------------------
//
//     dump
//
//--------------------------------
void Memoire::dump(long debut, long taille){
    long i=0;
    int nbItem=16;
    int cpt=0;
    long j=0;
    char car;
    char tblCar[16];
    
    printf("%5ld :",i+debut);
    for (i=0 ; i < taille ; i ++){
        if (cpt >= nbItem){
            // on affiche les caracteres imprimables
            printf("\t");
            for (j=0 ; j < nbItem ; j++){
                car = tblCar[j];
                if (car >= 0x20 && car <= 0x7e){
                    printf("%c",car);
                }else{
                    printf(".");
                }
            }
            j=0;
            // on affiche le debut de la nouvelle ligne
            printf("\n%5ld :",i+debut);
            if (cpt >= nbItem){
                cpt = 0;
            }
        }
        cpt++;
        if (debut + i >= MEMORY_SIZE){
            printf("\nERROR pointer out of limits\n");
            return;
        }
        printf(" %02x", memoireOS[debut + i]);
        tblCar[j++]=memoireOS[debut + i];
    }
    // On complete la fin de ligne avant les caracteres imprimante
    int debut1 = debut + i;
    int fin = debut1 - j + 16;
    for (int k = debut1 ; k < fin ; k++){
        printf("   ");
    }
    // on affiche les caracteres imprimable de la derniere ligne incomplete
    int first = debut + i - j;
    int last = first + j;
    printf("\t");
    for (i = first ; i < last ; i++){
        car = memoireOS[i];
        if (car >= 0x20 && car <= 0x7e){
            printf("%c",car);
        }else{
            printf(".");
        }
    }
    printf("\n");
}


//--------------------------------
//
//     garbageCollector
//
//--------------------------------
void Memoire::garbageCollector(int mode){
    //std::cout << "Lancement du garbage collector en mode ";
    if (firstBlocMemoire == NULL){
        std::cout << "ERROR : memory blocs table not initialized\n";
        return;
    }
    switch (mode){
        case GC_SIMPLE:
            // on parcours la table des blocs memoire a la recherche des blocs libres
            BlocMemoire *blocCourant;
            BlocMemoire *blocSuivant;
            blocCourant = firstBlocMemoire;
            while (1){
                //std::cout << "analyse de " << blocCourant->getName() << "\n";
                if (blocCourant->getStatus() == MEM_STATUS_FREE){
                    // ce bloc est libre on regarde si le bloc suivant l'est aussi
                    if (blocCourant->getNextBloc() != NULL){
                        blocSuivant = blocCourant->getNextBloc();
                        //std::cout << "     test avec  " << blocSuivant->getName() << "\n";
                        if (blocSuivant->getIdStockage() != blocCourant->getIdStockage()){
                            // ce bloc n'est pas dans la meme zone memoire
                            //std::cout << "     pas la meme zone de stockage \n";
                        }else{
                            if (blocSuivant->getStatus() == MEM_STATUS_FREE){
                                // le bloc suivant est libre lui aussi on peut concatener
                                //std::cout << "     on concatene les blocs \n";
                                blocCourant->concatBlocs();
                                // on continue l'analyse avec ce bloc
                                continue;
                            }                    
                        }
                    }
                }
                if (blocCourant->getNextBloc() != NULL){
                // on passe a l'analyse du bloc suivant
                    //std::cout << "     on passe au bloc suivant \n";
                    blocCourant = blocCourant->getNextBloc();
                }else{
                    // plus de blocs on arrete
                    //std::cout << "     plus de blocs \n";
                    return;
                }
            }
            break;
        case GC_FULL:
            std::cout << "to be completed\n";
            break;
        default:
            std::cout <<  "ERROR : invalid value for garbage collector mode : " << mode <<"\n";
            break;
    }

}
