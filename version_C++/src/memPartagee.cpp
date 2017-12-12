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



void afficheMemPartagee(structMemPartagee *ptr){
	std::cout << "\nContenu de la structure MemPartagée\n";
	std::cout << "ptrMemPartagee       : " << ptr << "\n";
	std::cout << "    nomMemPartagee   : " << ptr->nomMemPartagee << "\n";
	std::cout << "    firstBlocMemoire : " << ptr->firstBlocMemoire << "\n";
	std::cout << "\n";
}


MemPartagee::MemPartagee(void){
	std::cout << "\nMemPartagee : constructeur\n";
}


void MemPartagee::affErrno(void){
	switch(errno){
		case EACCES:
			std::cout << "memPartagee : error EACCES\n";
			break;
		case EEXIST:
			std::cout << "memPartagee : error EEXIST\n";
			break;
		case EINVAL:
			std::cout << "memPartagee : error EINVAL\n";
			break;
		default:
			std::cout << "memPartagee : error inconnue : " << errno << "\n";
			break;
	}
}

void MemPartagee::initMemPartagee(structMemPartagee *maStructMemPartagee, char *nom, BlocMemoire *firstBlocMemoire){
	int taille=sizeof(structMemPartagee);
	ptrMemPartagee=maStructMemPartagee;
	setNom(nom);
	setFirstBlocMemoire(firstBlocMemoire);
	structMemPartagee *ptr;
	std::cout << "\nMemPartagee : initMemPartagee (taille = " << taille << ")\n";
	// on cree 
	if ((memId = shmget(CLEF, sizeof(structMemPartagee), 0666  | IPC_CREAT)) < 0)	{
		//	et je m'assure que l'espace mémoire a été correctement créé
		std::cout << "MemPartagee : initMemPartagee : ERROR shmget (" << errno << ")\n";
		perror("shmget");
		affErrno();
		exit(-1);
	}
	std::cout << "MemPartagee : initMemPartagee : shmget ok : memId = " << memId << "\n";

	// J'attache le segment de mémoire partagée identifié par mem_ID au segment de données 
	// du processus A dans une zone libre déterminée par le Système d'exploitation
	if ((ptr = (structMemPartagee *) shmat(memId, NULL, 0)) == (void*) -1){
		//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		std::cout << "MemPartagee : initMemPartagee : ERROR shmat (" << ptr << ")\n";
		perror("shmat");
		affErrno();
		exit(-1);
	}else{
		std::cout << "MemPartagee : initMemPartagee : shmat ok : ptr recupere = " << ptr << "\n";
	}
	ptr->firstBlocMemoire=firstBlocMemoire;
	strcpy(ptr->nomMemPartagee,nom);

	afficheMemPartagee(ptr);

	ptrMemPartagee=ptr;
	std::cout << "MemPartagee : initMemPartagee : ptrMemPartagee : " << ptrMemPartagee << "\n";
	//affiche();
}


void MemPartagee::getMemPartagee(void){	
	std::cout << "\nMemPartagee : getMemPartagee\n";
	structMemPartagee *ptr;

	// Je cherche le segment mémoire associé à CLEF et je récupère l'identificateur de ce segment mémoire... 
	// J'attribue des droits de lecture uniquement
	if ((memId = shmget(CLEF, sizeof(structMemPartagee), 0444)) < 0){
		//	et je m'assure que l'espace mémoire a été correctement créé
		std::cout << "MemPartagee : getMemPartagee : ERROR shmget (" << memId << ")\n";
		perror("shmget");
		affErrno();
		exit(-1);
	}
	std::cout << "MemPartagee : getMemPartagee : shmget ok : memId = " << memId << "\n";
	// J'attache le segment de mémoire partagée identifié par mem_ID_B au segment de données du processus B 
	// dans une zone libre déterminée par le Système d'exploitation
	if ((ptr = (structMemPartagee *)shmat(memId, NULL, 0)) == (void*) -1){
		//	et je m'assure que le segment de mémoire a été correctement attaché à mon processus
		std::cout << "MemPartagee : getMemPartagee : ERROR shmat (" << ptr << ")\n";
		perror("shmat");
		affErrno();
		exit(-1);
	}else{
		std::cout << "MemPartagee : getMemPartagee : shmat ok : ptr = " << ptr << "\n";
	}
	afficheMemPartagee(ptr);

	ptrMemPartagee=ptr;
	std::cout << "MemPartagee : getMemPartagee : ptrMemPartagee : " << ptrMemPartagee << "\n";
	//affiche();
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
	ptrMemPartagee->firstBlocMemoire=bloc;
	//std::cout << "MemPartagee : setFirstBlocMemoire : " << maStructMemPartagee->firstBlocMemoire << "\n";
}

BlocMemoire *MemPartagee::getFirstBlocMemoire(void){
	//std::cout << "MemPartagee : getFirstBlocMemoire : " << maStructMemPartagee->firstBlocMemoire << "\n";
	return ptrMemPartagee->firstBlocMemoire;
}

void MemPartagee::setNom(char *nom){
	strcpy(ptrMemPartagee->nomMemPartagee,nom);
}

char *MemPartagee::getNom(void){
	return ptrMemPartagee->nomMemPartagee;
}

void MemPartagee::affiche(void){
	std::cout << "\nContenu de l'objet MemPartagée\n";
	std::cout << "memId                : " << memId << "\n";
	std::cout << "ptrMemPartagee       : " << ptrMemPartagee << "\n";
	std::cout << "    nomMemPartagee   : " << getNom() << "\n";
	std::cout << "    firstBlocMemoire : " << getFirstBlocMemoire() << "\n";
	std::cout << "\n";
}


