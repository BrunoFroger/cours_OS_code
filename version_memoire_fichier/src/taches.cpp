//
//  taches.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstring>

#include "../inc/os.hpp"
#include "../inc/taches.hpp"
#include "../inc/memoire.hpp"
#include "../inc/console.hpp"
#include "../inc/tools.hpp"
#include "../inc/users.hpp"


extern Memoire maMemoire;
extern Users monUser;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Taches::Taches(){
    //std::cout << "\nTaches : constructeur\n";
}

//--------------------------------
//
//     init
//
//--------------------------------
void Taches::init(char *nomFichier){
    strcpy(filename,nomFichier);
    owner=0;
    openMemoryFile();
}


//--------------------------------
//
//     init
//
//--------------------------------
void Taches::openMemoryFile(){
    //std::cout << "\nTaches::init : ouverture  fichier memoire avec nom : " << nomFichier << "\n";
    //std::cout << "Taches::init => user = " << userId << "\n";
    //std::cout << "\nTaches::init : affectation du nom de user : " << userId << "\n";
    memoryFile = fopen(filename,"rb+");
    if (memoryFile == NULL){
    	//std::cout << "Taches::init : ouverture en wb+ de " <<filename << "\n";
	    memoryFile = fopen(filename,"wb+");
	}else{
		//std::cout << "Taches::init : ouverture en rb+ de " <<filename << "\n";
	}
    if (memoryFile == NULL){
    	std::cout << "ERROR : unable to open Memory File (NULL) : " << filename  << "\n";
    }
    tailleStructBloc = sizeof(structBloc);
   	//std::cerr << "Memoire : taille des blocs memoire : " << tailleStructBloc  << "\n";
}

//--------------------------------
//
//     creeBlocTache
//
//--------------------------------
void Taches::creeBlocTache(char *chaine, long taille, char *texte){
	char type[10]=BLOC_TYPE_TSK;
	int id = maMemoire.alloueBloc(taille, type, texte, monUser.getUserId());
	//std::cout << "Taches::lance => memoire allouee pour ce nouveau bloc id = " << id << " \n";
	maMemoire.blocWrite(id, 0, buffer);
	//std::cout << "Taches::lance => donnees ecrites dans le fichier\n";
	INFO("User %s create task %s", monUser.getName(), chaine);
}

//--------------------------------
//
//     lance
//
//--------------------------------
int Taches::lance(char *chaine){
	//std::cout << "Taches::lance => lancement de la tache : " << chaine << "\n";
	long taille;
	// on cherche le fichier sur le disque de ce programme externe
	char tmp[BUFF_SIZE];
	char params[NB_PARAMS][BUFF_SIZE];
	int i=0;
	strcpy(tmp,chaine);
	// on decompose les parametres
	strcpy(tmp,Console::getParam(chaine,i));
	while (strlen(tmp) > 0){
		strcpy(params[i],tmp);
		//std::cout << "Taches::lance =>  parametre trouvé : " << tmp << "\n";
		i++;
		strcpy(tmp,Console::getParam(chaine,i));
	}
	//std::cout << "Taches::lance => " << i << " parametres trouvés\n";

	// lire fichier (params[0])
	FILE *ficProgramme;
	ficProgramme = fopen(params[0],"r");
	if (ficProgramme == NULL){
    	//std::cout << "ERROR : unable to open program File (NULL) : " << params[0]  << "\n";
    	return -1;
	}
	// calculer sa taille
	taille=0;
	strcpy(buffer,"");
	while (!feof(ficProgramme)){
		fgets(tmp, BUFF_SIZE, ficProgramme);
		taille+=strlen(tmp);
		strcat(buffer,tmp);
	}
	//std::cout << "Taches::lance => taille du fichier = " << taille << " \n";

	creeBlocTache(chaine, taille, params[0]);
	return 0;
}

//--------------------------------
//
//     kill
//
//--------------------------------
int Taches::kill(char * chaine){
	//std::cout << "Taches::kill => tue la tache by nom : " << chaine << "\n";
	structBloc tmpBloc = maMemoire.getBloc(chaine);
	return kill(tmpBloc.id);
}
int Taches::kill(int id){
	//std::cout << "Taches::kill => tue la tache by id : " << id << "\n";
	structBloc tmpBloc = maMemoire.getBloc(id);
	if (tmpBloc.id == -1){
		std::cout << "ERROR : impossible to get bloc " << id << "\n";
		return -1;
	}
	if (strcmp(tmpBloc.type,BLOC_TYPE_TSK) != 0){
		std::cout << "ERROR : impossible to kill, this bloc is not a task : " << id << "\n";
		return -1;
	}
	if (tmpBloc.owner != monUser.getUserId()){
		printf("ERROR : impossible to kill task %s(owner=%d) with user %d (not owner)\n",tmpBloc.name, tmpBloc.owner, monUser.getUserId());
		return -1;
	}
	if (tmpBloc.id == id){
		INFO("User %s kill task %s", monUser.getName(), tmpBloc.name);
		maMemoire.libereBloc(id);
		return 0;
	}
	return -1;
}

//--------------------------------
//
//     listeTaches
//
//--------------------------------
void Taches::listeTaches(void){
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
	std::cout << "+-----+--------+--------+--------+----------------+---------------------------+\n";
	std::cout << "|  id | taille | status | UserId | Ptr datas      |  nom de la tache          |\n";
	std::cout << "+-----+--------+--------+--------+----------------+---------------------------+\n";
	while (tmp == tailleStructBloc){
		if (strcmp(tmpBloc.type, BLOC_TYPE_TSK) == 0){
			//std::cout << "Taches::listeBlocs : offset = " << offset << "; affichage du bloc n°" << tmpBloc.id << "\n";
			sprintf(ligne,"| %3d | %6ld | %5s  |   %3d  |",tmpBloc.id, tmpBloc.size,tmpBloc.status,tmpBloc.owner);
			std::cout << ligne;
			std::cout << " " << &tmpBloc.datas << " |";
			sprintf(ligne," %-25s |",tmpBloc.name);
			std::cout << ligne;
			std::cout << "\n";
			// on passe au bloc suivant
		}
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	std::cout << "+-----+--------+--------+--------+----------------+---------------------------+\n";
	fclose(memoryFile);
}


//--------------------------------
//
//     getNextTask
//
//--------------------------------
structTache Taches::getNextActiveTask(int priorityLevel){
	structTache tmp;
	
	// on cherhce une tache active avec un niveau de priorite 
	// le plus haut et au moins
	printf("Taches::getNextActiveTask => a ecrire\n");
	return tmp;
}

//--------------------------------
//
//     pushActiveTask
//
//--------------------------------
void Taches::pushActiveTask(structTache tache){
	printf("Taches::pushActiveTask => a ecrire\n");
}
