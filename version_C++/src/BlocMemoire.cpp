//
//  BlocMemoire.cpp
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

BlocMemoire *firstBlocMemoire=NULL;
extern MemPartagee memPartagee;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
BlocMemoire::BlocMemoire(){
	size = 0;
	ptr = -1;
	status = MEM_STATUS_FREE;
	nextBloc = NULL;
}

//--------------------------------
//
//     Init
//
//--------------------------------
void BlocMemoire::init(char *memory, int id, char *nom, long debut, long taille){
	stockage=memory;
	idStockage=id;
	strcpy(name,nom);
	ptr=debut;
	size=taille;
	nextBloc=NULL;
	status=MEM_STATUS_FREE;
}

//--------------------------------
//
//     getNextBloc
//
//--------------------------------
BlocMemoire *BlocMemoire::getNextBloc(void){
	return nextBloc;
}

//--------------------------------
//
//     getPtr
//
//--------------------------------
long BlocMemoire::getPtr(void){
	return ptr;
}

//--------------------------------
//
//     getSize
//
//--------------------------------
long BlocMemoire::getSize(void){
	return size;
}

//--------------------------------
//
//     getStatus
//
//--------------------------------
int BlocMemoire::getStatus(void){
	return status;
}
//--------------------------------
//
//     getName
//
//--------------------------------
char *BlocMemoire::getName(void){
	return name;
}

//--------------------------------
//
//     nbBlocs
//
//--------------------------------
int BlocMemoire::nbBlocs(void){
	int cpt=1;
	BlocMemoire *ptr = firstBlocMemoire;
	if (ptr != NULL){
		while (ptr->nextBloc != NULL){
			cpt++;
			ptr=ptr->nextBloc;
		}
	}else{
		cpt = 0;
	}
	return cpt;
}

//--------------------------------
//
//     getSubBloc
//
//--------------------------------
BlocMemoire *BlocMemoire::getSubBloc(char *memory, char *nom, BlocMemoire *precedent, long taille){
	BlocMemoire *newBloc, *blocCourant;

	// init du bloc courant
	blocCourant = this;

	// on initialise un nouveau bloc
	newBloc = (BlocMemoire *) malloc(sizeof(BlocMemoire));
	if (newBloc == NULL){
		std::cout << "ERROR : creation of sub bloc impossible (memory allocation error)";
		return NULL;
	}
	// il commence au debut du bloc courant avec sa taille
	newBloc->init(memory, idStockage, nom, ptr,taille);
	// son successeur est le bloc courant reduit de ce nouveau bloc
	newBloc->nextBloc = this;
	// il est marque comme utilisé
	newBloc->status = MEM_STATUS_USED;	
	if (ptr == 0){
		firstBlocMemoire=newBloc;
        memPartagee.setFirstBlocMemoire(firstBlocMemoire);
	}
	ptr += taille;
	size -= taille;
	status=MEM_STATUS_FREE;
	if (precedent != NULL){
		precedent->nextBloc=newBloc;
	}
	return newBloc;
}

//--------------------------------
//
//     affBlocDetail
//
//--------------------------------
void BlocMemoire::affBlocDetail(void){
    std::cout << "name   : " << name << "\n";
    std::cout << "ptr    : " << ptr << "\n";
    std::cout << "size   : " << size << "\n";
    switch (status){
        case MEM_STATUS_FREE:
            std::cout << "status : FREE\n";
            break;;
        case MEM_STATUS_USED: 
            std::cout << "status : USED\n";
            break;;
        default:
            std::cout << "status : N/A\n";
            break;;
    }
    if (nextBloc != NULL){
        std::cout << "next   : YES\n";
    }else{ 
        std::cout << "next   : NO\n";
    }
    std::cout << "\n";
}

//--------------------------------
//
//     freeBloc
//
//--------------------------------
void BlocMemoire::freeBloc(void){
	status=MEM_STATUS_FREE;
}

//--------------------------------
//
//     concatBlocs
//
//--------------------------------
int BlocMemoire::concatBlocs(void){
	BlocMemoire *suivant;
	if (nextBloc != NULL){
		suivant = nextBloc;
	}else{
		std::cout << "ERROR : no other bloc to perform concatenation\n";
		return KO;
	}
	// on recupere le bloc suivant de tmp
	if (suivant->getNextBloc() != NULL){
		// on change le pointeur nextBloc du bloc courant 
		// avec le nextBloc du suivant
		nextBloc = suivant->getNextBloc();
		size += suivant->getSize();
		suivant->libere();
		suivant->affBlocDetail();
	}
	return OK;
}

//--------------------------------
//
//     affBlocs
//
//--------------------------------
void BlocMemoire::affBlocs(void){
	BlocMemoire *bloc= firstBlocMemoire;
	if (firstBlocMemoire == NULL){
		std::cout << "ERROR : no blocs found\n"; 
	}else{
		std::cout << "+-----------------------------------------------------------------+\n";
		std::cout << "|    blocs memoire                                                |\n";
		std::cout << "+-----------------------------------------------------------------+\n";
		std::cout << "|   name               | pos   | size   | status | next | Id Bloc |\n";
		std::cout << "+----------------------+-------+--------+--------+------+---------+\n";
		int continuer = 1;
		do{
			printf("| %20s | %5ld | %6ld",bloc->name, bloc->getPtr(), bloc->getSize());
			switch (bloc->getStatus()){
				case MEM_STATUS_FREE:
					std::cout << " | FREE   |";
					break;;
				case MEM_STATUS_USED: 
					std::cout << " | USED   |";
					break;;
				default:
					std::cout << " | N/A    |";
					break;;
			}
			if (bloc->nextBloc != NULL){
				std::cout << " YES  |";
			}else{
				std::cout << " NO   |";
				continuer = 0;
			}
			printf("    %2d   |",bloc->idStockage);
			bloc = bloc->nextBloc;
			std::cout << "\n";
		}
		while (continuer == 1);
		std::cout << "+----------------------+-------+--------+--------+------+---------+\n";
	}
}

//--------------------------------
//
//     fill
//
//--------------------------------
int BlocMemoire::fill(long offset, void *data, long dataSize){
    long i;
    long index;
    index = ptr + offset;
    char *tmpData = (char *)data;

    if ( (ptr + offset + dataSize) > size){
        std::cout << "ERROR : data out of range\n";
        return KO;
    }
    for (i = 0 ; i < dataSize ; i++){
        if (stockage == NULL){
        	std::cout << "ERROR : link to memory not initialized\n";
 	       return KO;
        }
        stockage[index + i] = tmpData[i];
    }
    return OK;
}

//--------------------------------
//
//     libere
//
//--------------------------------
void BlocMemoire::libere(){
	std::cout << "Liberation memoire du bloc " << name << "\n";
    free(this);
}

//--------------------------------
//
//     link
//
//--------------------------------
int BlocMemoire::link(BlocMemoire *bloc){
	nextBloc = bloc;
	//firstBlocMemoire = this;
    return OK;
}

//--------------------------------
//
//     getIdStockage
//
//--------------------------------
int BlocMemoire::getIdStockage(void){
    return idStockage;
}


