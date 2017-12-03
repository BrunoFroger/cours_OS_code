//
//  memPartagee.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "../inc/os.hpp"
#include "../inc/memoire.hpp"
#include "../inc/memPartagee.hpp"

int memId;
extern BlocMemoire *firstBlocMemoire;
extern structMemPartagee *maStructMemPartagee;

MemPartagee::MemPartagee(void){
	std::cout << "\n\nMemPartagee : constructeur\n";
}


void MemPartagee::affErrno(void){
	switch(errno){
		case EACCES:
			std::cout << "error EACCES\n";
			break;
		case EEXIST:
			std::cout << "error EEXIST\n";
			break;
		case EINVAL:
			std::cout << "error EINVAL\n";
			break;
		default:
			std::cout << "error inconnue : " << errno << "\n";
			break;
	}
}

void MemPartagee::initMemPartagee(structMemPartagee *maStructMemPartagee, char *nom, BlocMemoire *firstBlocMemoire){
	int taille=sizeof(structMemPartagee);
	std::cout << "\n\nMemPartagee : initMemPartagee (taille = " << taille << ")\n";
	// on cree 
	if ((memId = shmget(CLEF, sizeof(structMemPartagee), 0666  | IPC_CREAT)) < 0)	{
		//	et je m'assure que l'espace mémoire a été correctement créé
		std::cout << "MemPartagee : initMemPartagee : ERROR shmget (" << errno << ")\n";
		affErrno();
		perror("shmget");
		exit(-1);
	}
	std::cout << "MemPartagee : initMemPartagee : shmget ok : memId = " << memId << "\n";

	// J'attache le segment de mémoire partagée identifié par mem_ID au segment de données 
	// du processus A dans une zone libre déterminée par le Système d'exploitation
	if ((maStructMemPartagee = (structMemPartagee *) shmat(memId, NULL, 0)) == (void*) -1){
		//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		std::cout << "MemPartagee : initMemPartagee : ERROR shmat (" << maStructMemPartagee << ")\n";
		perror("shmat");
		exit(-1);
	}
	std::cout << "MemPartagee : initMemPartagee : shmat ok : maStructMemPartagee : " << maStructMemPartagee << "\n";

	std::cout << "MemPartagee : initMemPartagee : initialistaion des datas de la memoire partagée\n";
	strcpy(maStructMemPartagee->nomMemPartagee,nom);
	std::cout << "MemPartagee : initMemPartagee : init nom (" << nom << ")\n";
	maStructMemPartagee->firstBlocMemoire=firstBlocMemoire;
	std::cout << "MemPartagee : initMemPartagee : init firstBlocMemoire (" << firstBlocMemoire << ")\n";
	ptrMemPartagee = maStructMemPartagee;
	return;
}


structMemPartagee *MemPartagee::getMemPartagee(void){
	structMemPartagee *ptr;
	std::cout << "\n\nMemPartagee : getMemPartagee\n";

	ptr=NULL;

	// Je cherche le segment mémoire associé à CLEF et je récupère l'identificateur de ce segment mémoire... 
	// J'attribue des droits de lecture uniquement
	if ((memId = shmget(CLEF, sizeof(structMemPartagee), 0444)) < 0){
		//	et je m'assure que l'espace mémoire a été correctement créé
		std::cout << "MemPartagee : getMemPartagee : ERROR shmget (" << memId << ")\n";
		perror("shmget");
		exit(-1);
	}
	std::cout << "MemPartagee : getMemPartagee : shmget ok : memId = " << memId << "\n";
	// J'attache le segment de mémoire partagée identifié par mem_ID_B au segment de données du processus B 
	// dans une zone libre déterminée par le Système d'exploitation
	if ((ptr = (structMemPartagee *)shmat(memId, NULL, 0)) == (void*) -1){
		//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		std::cout << "MemPartagee : getMemPartagee : ERROR shmat (" << ptrMemPartagee << ")\n";
		perror("shmat");
		exit(-1);
	}
	std::cout << "MemPartagee : getMemPartagee : shmat ok : ptrMemPartagee = " << ptr << "\n";
	return ptr;
}

void MemPartagee::killMemPartagee(structMemPartagee *ptr){/*
	if ((memId = shmget(CLEF, sizeof(structMemPartagee), 0444)) < 0){
		//	et je m'assure que l'espace mémoire a été correctement créé
		std::cout << "MemPartagee : killMemPartagee : ERROR shmget (" << memId << ")\n";
		perror("shmget");
		exit(-1);
	}
	std::cout << "MemPartagee : killMemPartagee : shmget ok : memId = " << memId << "\n";

	if ((ptr = (structMemPartagee *)shmdt(memId, NULL, 0)) == (void*) -1){
		//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		std::cout << "MemPartagee : getMemPartagee : ERROR shmat (" << ptrMemPartagee << ")\n";
		perror("shmat");
		exit(-1);
	}*/
}

void MemPartagee::setFirstBlocMemoire(BlocMemoire *bloc){
	//std::cout << "MemPartagee : setFirstBlocMemoire : firstBlocMemoire = " << maStructMemPartagee->firstBlocMemoire << "\n";
	maStructMemPartagee->firstBlocMemoire=bloc;
}

BlocMemoire *MemPartagee::getFirstBlocMemoire(void){
	//std::cout << "MemPartagee : getFirstBlocMemoire : firstBlocMemoire = " << maStructMemPartagee->firstBlocMemoire << "\n";
	return maStructMemPartagee->firstBlocMemoire;
}

void MemPartagee::setNom(char *nom){
	strcpy(maStructMemPartagee->nomMemPartagee,nom);
}

char *MemPartagee::getNom(void){
	return maStructMemPartagee->nomMemPartagee;
}

void MemPartagee::affiche(void){
	std::cout << "\n\nContenu de l'objet MemPartagée\n";
	std::cout << "memId                : " << memId << "\n";
	std::cout << "ptrMemPartagee       : " << ptrMemPartagee << "\n";
	std::cout << "    nomMemPartagee   : " << nomMemPartagee << "\n";
	std::cout << "    firstBlocMemoire : " << firstBlocMemoire << "\n";
	std::cout << "nomMemPartagee       : " << nomMemPartagee << "\n";
	std::cout << "firstBlocMemoire     : " << firstBlocMemoire << "\n";
	std::cout << "\n";
}

