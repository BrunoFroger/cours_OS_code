//
//  users.cpp
//  OS
//
//  Created by Bruno FROGER on 03/01/2018.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#include <cstdio>
#include <iostream>
#include <cstring>

#include "../inc/os.hpp"
#include "../inc/users.hpp"
#include "../inc/memoire.hpp"
#include "../inc/taches.hpp"


extern Memoire maMemoire;
extern Taches mesTaches;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Users::Users(){
    //std::cout << "Users::Users : constructeur\n";

}

//--------------------------------
//
//     init
//
//--------------------------------
void Users::init(char *nomFichier, int id, char *name){
    userId=id;
    strcpy(userName,name);
    strcpy(filename,nomFichier);
    openMemoryFile();
}

//--------------------------------
//
//     openMemoryFile
//
//--------------------------------
void Users::openMemoryFile(){
    //std::cout << "\Users::init : ouverture  fichier memoire avec nom : " << nomFichier << "\n";
    memoryFile = fopen(filename,"rb+");
    if (memoryFile == NULL){
    	//std::cout << "Users::init : ouverture en wb+ de " <<filename << "\n";
	    memoryFile = fopen(filename,"wb+");
	}else{
		//std::cout << "Users::init : ouverture en rb+ de " <<filename << "\n";
	}
    if (memoryFile == NULL){
    	std::cout << "ERROR : unable to open Memory File (NULL) : " << filename  << "\n";
    }
    tailleStructBloc = sizeof(structBloc);
   	//std::cerr << "Users : taille des blocs memoire : " << tailleStructBloc  << "\n";
}

//--------------------------------
//
//     getLastUserId
//
//--------------------------------
int Users::getLastUserId(void){
    // recuperation du dernier userId cree dans le fichier memoire
    int nbBlocs = maMemoire.nbBlocs();
    //std::cout << "Users::getLastUserId : nb Blocs trouves : " << nbBlocs << "\n";
    int lastUserId=0;
    for (int i = 0 ; i < nbBlocs ; i++){
    	structBloc tmpBloc = maMemoire.getBloc(i);
    	//std::cout << "Users::getLastUserId : analyse du bloc " << tmpBloc.id << "\n";
    	if (tmpBloc.size != -1){
    		//std::cout << "Users::getLastUserId : lastUserId : " << lastUserId << "; userId du bloc : " << tmpBloc.owner << "; type du bloc : " << tmpBloc.type <<  "\n";
    		if (strcmp(tmpBloc.type,BLOC_TYPE_USR) == 0){
    			// on 	a trouve un bloc user, on memorise le userId associé
    			//std::cout << "Users::getLastUserId : on a trouve un bloc de type USR => lastUserId : " << lastUserId << "; userId du bloc : " << tmpBloc.owner <<  "\n";
    			lastUserId = tmpBloc.owner;
    		}
    	}
    }
	//std::cout << "Users::getLastUserId : lastUserId : " << lastUserId << "\n";
    return lastUserId;
}


//--------------------------------
//
//     getNewUserId
//
//--------------------------------
int Users::getNewUserId(void){
	int id;
	id = getLastUserId();
	id++;
	return id;
}


//--------------------------------
//
//     setName
//
//--------------------------------
void Users::setName(char *name){
	strcpy(userName,name);
}

//--------------------------------
//
//     getName
//
//--------------------------------
char *Users::getName(void){
	return userName;
}


//--------------------------------
//
//     getName
//
//--------------------------------
int Users::getUserId(void){
	return userId;
}


//--------------------------------
//
//     listeUsers
//
//--------------------------------
void Users::listeUsers(void){
	char ligne[50];
	long offset=0;
	structBloc tmpBloc;
    openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	//std::cout << "Taches::listeBlocs : nombre de caracteres lus : " << tmp <<  " " << tailleStructBloc << "\n";
	// affichage de l'entete
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		return;
	}
	std::cout << "+-----+-----------------------------------------------------+\n";
	std::cout << "|  id | nom                                                 |\n";
	std::cout << "+-----+-----------------------------------------------------+\n";
	while (tmp == tailleStructBloc){
		//std::cout << "analyse du bloc " << tmpBloc.id << "\n";
		if (strcmp(tmpBloc.type, BLOC_TYPE_USR) == 0){
			//std::cout << "Taches::listeBlocs : offset = " << offset << "; affichage du bloc n°" << tmpBloc.id << "\n";
			sprintf(ligne,"| %3d | %-50s  |",tmpBloc.owner, tmpBloc.name);
			std::cout << ligne;
			std::cout << "\n";
			// on passe au bloc suivant
		}
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	std::cout << "+-----+-----------------------------------------------------+\n";
    fclose(memoryFile);
    std::cout << "Users::listeUsers : fin d'affichage\n";
    printf("fin de boucle a debugger trap 6, ecriture hors de la memoire allouee\n");
}

//--------------------------------
//
//     kill
//
//--------------------------------
void Users::kill(void){
	// supprime tout ce qui a ete lancé par ce user
	long offset=0;
	structBloc tmpBloc;
    openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		return;
	}
	while (tmp == tailleStructBloc){
		//std::cout << "Users::kill => analyse du bloc " << tmpBloc.id << "\n";
		if (tmpBloc.owner == userId){
			//std::cout << "               le bloc " << tmpBloc.id << " appartient au user " << userId << "\n";
			if (strcmp(tmpBloc.type, BLOC_TYPE_TSK) == 0){
				// c'est une tache on lance la descrution de cette tache
				//std::cout << "               c'est une tache => bloc " << tmpBloc.id << " detruit\n";
				mesTaches.kill(tmpBloc.id);
			}
			// on passe au bloc suivant
		}
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	fclose(memoryFile);
	//std::cout << "Users::kill => fin de fonction\n";
}


//--------------------------------
//
//     nbUsers
//
//--------------------------------
int Users::nbUsers(void){
	long offset=0;
	int cpt=0;
	structBloc tmpBloc;
    openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		return -1;
	}
	while (tmp == tailleStructBloc){
		if ((strcmp(tmpBloc.type,BLOC_TYPE_USR) == 0) && (tmpBloc.owner != -1)){
			//printf("un user trouvé %d\n",tmpBloc.id);
			cpt++;
		}
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	fclose(memoryFile);
	//printf("nombre de users trouvés %d\n",cpt);
	return cpt;
}
