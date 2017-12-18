//
//  Memoire.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#include <iostream>
#include <cstdio>

#include "../inc/memoire.hpp"

char nom[50];

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Memoire::Memoire(){
    //std::cout << "\nMemoire : constructeur\n";
    strcpy(nom,"defaultMemory.dta");
    Memoire(nom);
}

Memoire::Memoire(char *nomFichier){
    std::cout << "\nMemoire : constructeur fichier memoire avec nom : " << nomFichier << "\n";
    strcpy(filename,nomFichier);
    memoryFile = fopen(filename,"wb+");
    if (memoryFile == NULL){
    	std::cerr << "ERROR : unable to open Memory File (NULL) : " << filename  << "\n";
    }
    tailleStructBloc = sizeof(structBloc);
   	//std::cerr << "Memoire : taille des blocs memoire : " << tailleStructBloc  << "\n";
}

//--------------------------------
//
//     memWrite
//
//--------------------------------
long Memoire::memWrite(long offset, char *datas){
	fseek(memoryFile, offset, 0);
	fflush(memoryFile);
	long nb = strlen(datas);
	nb = fwrite (datas, 1, nb, memoryFile);
	//std::cout << "memWrite : nombre de caracteres ecris : " << nb << "\n";
	fflush(memoryFile);
	return nb;
}

//--------------------------------
//
//     memRead
//
//--------------------------------
char * Memoire::memRead(long offset, long nb){
	//std::cout << "memRead : essai de lecture de : " << nb << " caracteres a partir de " << offset << "\n";
	if (nb >= MAX_BUFFER){
		std::cout << "ERROR : data size to read in memory is too big (" << nb << "\n";
		return -1;
	}
	fseek(memoryFile, offset, 0);
	fflush(memoryFile);
	long tmp ;
	tmp = fread(buffer, 1, (size_t) nb, memoryFile);
	//std::cout << "memRead : nombre de caracteres lus : " << tmp << " [" << &buffer << "]\n";
	return buffer;
}

//--------------------------------
//
//     display
//
//--------------------------------
void Memoire::display(long offset, long nb){
	//std::cout << "display : essai de display de : " << nb << " caracteres a partir de " << offset << "\n";
	memRead(offset,nb);
	// le resultat de memRead est dans la variable priveee buffer
	int nbItemParLigne = 16;
	int idItem=0;
	char asciiItems[25];
	unsigned char car;

	//std::cout << "display : display " << nb << " caracteres a partir de : " << offset << "\n";
	long i = 0;
	printf("%4ld :",i);
	for (i = 0 ; i <= nb ; i++){
		if (idItem >= nbItemParLigne){
			// affichage des caracteres en representation ascii
			for (int j = 0 ; j < nbItemParLigne ; j++){
				car = asciiItems[j];
				if (car >= 0x20 && car <= 0x7e){
					printf("%c",car);
				}else{
					printf(".");
				}
			}
			printf("\n%4ld :",i);
			idItem = 0;
		}
		car=buffer[i]; 
		asciiItems[idItem++]=car;
		printf("%02x ",car);
	}
	std::cout << "\n";
}


//--------------------------------
//
//     alloueBloc
//
//--------------------------------
int Memoire::alloueBloc(long taille){
	int id=0;
	structBloc tmpBloc;
	long offset=0;
	fseek(memoryFile, offset, 0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	while (tmp == tailleStructBloc){
		// un bloc a ete lu
		// on lit le suivant
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
		id=tmpBloc.id;
		//std::cout << "bloc n°" << id << " trouvé \n";
		id++;
	}
	//std::cout << "offset = " << offset << "; creation du bloc n°" << id << "\n";
	strcpy(tmpBloc.debut,"[debut]");
	strcpy(tmpBloc.fin,"[fin]");
	tmpBloc.id=id;
	tmpBloc.size=taille;
	strcpy(tmpBloc.status,BLOC_USED);
	sprintf(tmpBloc.name,"bloc %d",id);
	tmpBloc.datas = malloc(tailleStructBloc);
	fwrite(&tmpBloc,(size_t)tailleStructBloc,1,memoryFile);
	//afficheBloc(tmpBloc);
	return id;
}

//--------------------------------
//
//     getBloc
//
//--------------------------------
structBloc Memoire::getBloc(int id){
	structBloc tmpBloc;
	long offset=tailleStructBloc*id;
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	if (tmp == tailleStructBloc){
		return tmpBloc;
	}
	tmpBloc.id=-1;
	tmpBloc.size=0;
	return tmpBloc;
}


//--------------------------------
//
//     afficheBloc
//
//--------------------------------
void Memoire::afficheBloc(structBloc bloc){
	std::cout << "\nAffichage du contenu d'un bloc\n";
	if (bloc.id == -1){
		std::cout << "ERROR bloc id " << bloc.id << " is invalid\n";
		return;
	}
	std::cout << "id        : " << bloc.id << "\n";
	std::cout << "nom       : " << bloc.name << "\n";
	std::cout << "taille    : " << bloc.size << "\n";
	std::cout << "ptr datas : " << bloc.datas << "\n";
	std::cout << "\n";
}

//--------------------------------
//
//     listeBlocs
//
//--------------------------------
void Memoire::listeBlocs(void){
	char ligne[50];
	long offset=0;
	structBloc tmpBloc;
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	//std::cout << "listeBlocs : nombre de caracteres lus : " << tmp <<  " " << tailleStructBloc << "\n";
	// affichage de l'entete
	std::cout << "+-----+--------+--------+----------------+---------------------------+\n";
	std::cout << "|  id | taille | status | Ptr datas      |  nom du bloc              |\n";
	std::cout << "+-----+--------+--------+----------------+---------------------------+\n";
	while (tmp == tailleStructBloc){
		//std::cout << "offset = " << offset << "; affichage du bloc n°" << tmpBloc.id << "\n";
		sprintf(ligne,"| %3d | %6ld | %5s  |",tmpBloc.id, tmpBloc.size,tmpBloc.status);
		std::cout << ligne;
		std::cout << " " << tmpBloc.datas << " |";
		sprintf(ligne," %-25s |",tmpBloc.name);
		std::cout << ligne;
		std::cout << "\n";
		// on passe au bloc suivant
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	std::cout << "+-----+--------+--------+----------------+---------------------------+\n";
}

