//
//  Memoire.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#include <iostream>
#include <cstdio>
#include <cstring>

#include "../inc/memoire.hpp"
#include "../inc/os.hpp"
#include "../inc/users.hpp"
#include "../inc/tools.hpp"

extern Users monUser;
char nom[50];

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Memoire::Memoire(){
    //std::cout << "\nMemoire : constructeur\n";
}

//--------------------------------
//
//     init
//
//--------------------------------
void Memoire::init(char *nomFichier){
    strcpy(filename,nomFichier);
	openMemoryFile();
}

//--------------------------------
//
//     openMemoryFile
//
//--------------------------------
void Memoire::openMemoryFile(void){
    //std::cout << "\nMemoire : initialisation fichier memoire avec nom : " << filename << "\n";
    memoryFile = fopen(filename,"rb+");
    if (memoryFile == NULL){
    	//std::cout << "Memoire::init : ouverture en wb+ de " <<filename << "\n";
	    memoryFile = fopen(filename,"wb+");
	}else{
		//std::cout << "Memoire::init : ouverture en rb+ de " <<filename << "\n";
	}
    if (memoryFile == NULL){
    	std::cout << "ERROR : unable to open Memory File (NULL) : " << filename  << "\n";
    }
    tailleStructBloc = sizeof(structBloc);
   	//std::cerr << "Memoire : taille des blocs memoire : " << tailleStructBloc  << "\n";
    //std::cout << "\nMemoire : fin initialisation fichier memoire avec nom : " << nomFichier << "\n";
}

//--------------------------------
//
//     memWrite
//
//--------------------------------
long Memoire::memWrite(long offset, char *datas){
	openMemoryFile();
	fseek(memoryFile, offset, 0);
	fflush(memoryFile);
	long nb = strlen(datas);
	nb = fwrite (datas, 1, nb, memoryFile);
	//std::cout << "memWrite : nombre de caracteres ecris : " << nb << "\n";
	fflush(memoryFile);
	fclose(memoryFile);
	return nb;
}

//--------------------------------
//
//     memRead
//
//--------------------------------
char * Memoire::memRead(long offset, long nb){
	std::cout << "memRead : essai de lecture de : " << nb << " caracteres a partir de " << offset << "\n";
	if (nb >= MAX_BUFFER){
		std::cout << "ERROR : data size to read in memory is too big (" << nb << "\n";
		return NULL;
	}
	fseek(memoryFile, offset, 0);
	fflush(memoryFile);
	long tmp ;
	tmp = fread(buffer, 1, (size_t) nb, memoryFile);
	std::cout << "memRead : nombre de caracteres lus : " << tmp << " [" << &buffer << "]\n";
	return buffer;
}

//--------------------------------
//
//     dump
//
//--------------------------------
void Memoire::dump(long offset, long nb){
	int nbItemParLigne = 16;
	int idItem=0;
	char asciiItems[25];
	unsigned char car;

	//std::cout << "display : display " << nb << " caracteres a partir de : " << offset << "\n";
	long i = 0;
	printf("%4ld :",offset + i);
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
			printf("\n%4ld :",offset + i);
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
//     display
//
//--------------------------------
void Memoire::display(long offset, long nb){
	std::cout << "display : essai de display de : " << nb << " caracteres a partir de " << offset << "\n";
	memRead(offset,nb);
	// le resultat de memRead est dans la variable priveee buffer
	dump(offset, nb);
}


//--------------------------------
//
//     alloueBloc
//
//--------------------------------
int Memoire::alloueBloc(long taille,char *blocType){
	// initialiser le nom du bloc pour l'autre methode
	return alloueBloc(taille, blocType, (char *) NULL,0);
}

int Memoire::alloueBloc(long taille,char *blocType, char *blocName){
	return alloueBloc(taille, blocType, blocName, 0);
}

int Memoire::alloueBloc(long taille,char *blocType, int userId){
	return alloueBloc(taille, blocType, NULL, userId);
}

int Memoire::alloueBloc(long taille,char *blocType, char *blocName, int userId){
	int id=0;
	structBloc tmpBloc;
	long offset=0;
	char tmpName[50];

	if (blocName == NULL){
		blocName = tmpName;
		sprintf(blocName,"bloc %d",id);
	}
	/*
	std::cout << "Memoire::alloueBloc : allocation d'un bloc\n";
	std::cout << "                      Taille   = " << taille << "\n";
	std::cout << "                      Type     = " << blocType << "\n";
	std::cout << "                      blocName = " << blocName << "\n";
	std::cout << "                      UserId   = " << userId << "\n";
	*/
	openMemoryFile();
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
	tmpBloc.owner=userId;
	strcpy(tmpBloc.type,blocType);
	strcpy(tmpBloc.status,BLOC_USED);
	strcpy(tmpBloc.name,blocName);
	tmpBloc.datas = (char *)malloc(taille);
	fwrite(&tmpBloc,(size_t)tailleStructBloc,1,memoryFile);
	//afficheBloc(tmpBloc);
	fflush(memoryFile);
	fclose(memoryFile);
	//std::cout << "Memoire::alloueBloc : fin allocation d'un bloc\n";
	return id;
}

//--------------------------------
//
//     getBloc
//
//--------------------------------
structBloc Memoire::getBloc(int id){
	//std::cout << "Memoire::getBloc => id " << id << "\n";
	structBloc tmpBloc;
	long offset=0;
	openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	while (tmp == tailleStructBloc){
		//std::cout << "Memoire::getBloc => analyse du bloc " << tmpBloc.id << "\n";
		if (tmpBloc.id == id){
			fclose(memoryFile);
			//std::cout << "Memoire::getBloc => bloc trouve " << id << "\n";
			return tmpBloc;
		}
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	tmpBloc.id=-1;
	tmpBloc.size=0;
	fclose(memoryFile);
	//std::cout << "Memoire::getBloc => pas de bloc trouve avec cet id " << id << "\n";
	return tmpBloc;
}
structBloc Memoire::getBloc(char *chaine){
	//std::cout << "Memoire::getBloc => chaine " << chaine << "\n";
	structBloc tmpBloc;
	long offset=0;
	openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	while (tmp == tailleStructBloc){
		if (strcmp(tmpBloc.name,chaine) == 0){
			fclose(memoryFile);
			return tmpBloc;
		}
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	tmpBloc.id=-1;
	tmpBloc.size=0;
	fclose(memoryFile);
	return tmpBloc;
}


//--------------------------------
//
//     afficheBloc
//
//--------------------------------
void Memoire::afficheBloc(structBloc bloc){
	std::cout << "Affichage du contenu d'un bloc\n";
	if (bloc.id == -1){
		std::cout << "ERROR bloc id " << bloc.id << " is invalid\n";
		return;
	}
	std::cout << "type      : " << bloc.type << "\n";
	std::cout << "id        : " << bloc.id << "\n";
	std::cout << "nom       : " << bloc.name << "\n";
	std::cout << "owner     : " << bloc.owner << "\n";
	std::cout << "taille    : " << bloc.size << "\n";
	std::cout << "status    : " << bloc.status << "\n";
	std::cout << "ptr datas : " << &bloc.datas << "\n";
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
	openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	//std::cout << "listeBlocs : nombre de caracteres lus : " << tmp <<  " " << tailleStructBloc << "\n";
	// affichage de l'entete
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		return;
	}
	//std::cout << " first data bloc : " << tmpBloc.datas << "\n";
	std::cout << "+-----+------+--------+--------+--------+----------------+---------------------------+\n";
	std::cout << "|  id | type | taille | status | UserId | Ptr datas      |  nom du bloc              |\n";
	std::cout << "+-----+------+--------+--------+--------+----------------+---------------------------+\n";
	while (tmp == tailleStructBloc){
		//std::cout << "offset = " << offset << "; affichage du bloc n°" << tmpBloc.id << "\n";
		sprintf(ligne,"| %3d |  %3s | %6ld | %5s  |   %3d  |",tmpBloc.id, tmpBloc.type, tmpBloc.size,tmpBloc.status,tmpBloc.owner);
		std::cout << ligne;
		sprintf(ligne, " %14p |",tmpBloc.datas);
		std::cout << ligne;
		//std::cout << " " << tmpBloc.datas << " |";
		sprintf(ligne," %-25s |",tmpBloc.name);
		std::cout << ligne;
		std::cout << "\n";
		// on passe au bloc suivant
		offset+=tailleStructBloc;
		fseek(memoryFile,offset,0);
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	std::cout << "+-----+------+--------+--------+--------+----------------+---------------------------+\n";
	fclose(memoryFile);
}


//--------------------------------
//
//     nbBlocs
//
//--------------------------------
int Memoire::nbBlocs(void){
	int cpt=0;
	long offset=0;
	structBloc tmpBloc;
	openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	//std::cout << "listeBlocs : nombre de caracteres lus : " << tmp <<  " " << tailleStructBloc << "\n";
	// affichage de l'entete
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		fclose(memoryFile);
		return 0;
	}
	while (tmp == tailleStructBloc){
		cpt++;
		tmp = fread (&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	fclose(memoryFile);
	return cpt;
}

//--------------------------------
//
//     libereBloc
//
//--------------------------------
void Memoire::libereBloc(int id){

	long offset=0;
	structBloc tmpBloc;

	//std::cout << "Memoire::libereBloc : " << id << "\n";

	openMemoryFile();
	fseek(memoryFile,offset,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	//std::cout << "listeBlocs : nombre de caracteres lus : " << tmp <<  " " << tailleStructBloc << "\n";
	// affichage de l'entete
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		fclose(memoryFile);
		return;
	}
	while (tmp == tailleStructBloc){
		if (tmpBloc.id == id){
			//std::cout << "Memoire::libere => on a trouve l'id du bloc " << id << "\n";
			strcpy(tmpBloc.status,BLOC_FREE);
			tmpBloc.size=-1;
			tmpBloc.owner=-1;
			free (tmpBloc.datas);
			tmpBloc.datas=NULL;
			strcpy(tmpBloc.name,"");
			strcpy(tmpBloc.type,BLOC_TYPE_NA);
			//afficheBloc(tmpBloc);
			// on ecrit ce bloc sur le fichier
			long position =ftell(memoryFile);
			position -= tailleStructBloc;
			fseek(memoryFile,position,0);
			fwrite(&tmpBloc,(size_t)tailleStructBloc,1,memoryFile);
			fclose(memoryFile);
			return;
		}
		tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	}
	// on sort de la boucle sans avoir trouve le bloc concerne
	std::cout << "ERROR : bloc " << id << " inconnu\n";
	fclose(memoryFile);
}

//--------------------------------
//
//     kill
//
//--------------------------------

void Memoire::kill(void){
	kill(filename);
}
void Memoire::kill(char *filename){
	//printf("try to erase memory file on disk if exist : %s\n",filename);
	char commande[250];
	sprintf(commande,"if [ -f %s ]; then rm %s; fi;",filename, filename);

	//std::cout << "Memoire::kill : destruction du fichier memoire avec la commande : " << commande << "\n";
	//printf("Erase memory file on disk if exist\n");
	INFO("Erase memory file on disk if exist");
	system(commande);
}

//--------------------------------
//
//     blocWrite
//
//--------------------------------
long Memoire::blocWrite(int id, long offset, char *datas){
	//std::cout << "Memoire::blocWrite : Debut (en cours  ecriture)\n";
	//std::cout << "Memoire::blocWrite : id(" << id << ") ; offset(" << offset << ")\n";
	//std::cout << "Memoire::blocWrite : tentative d'ecriture de datas :\n";
	//std::cout << "-------------------------------------------\n";
	//std::cout << datas << "\n";
	//std::cout << "-------------------------------------------\n";
	char *ptr = getPtrData(id);
	//std::cout << "Memoire::blocWrite : ptr(" << &ptr << ")\n";
	ptr += offset;
	//std::cout << "Memoire::blocWrite : ecriture dans la memoire ; taille = " << strlen(datas) << "\n";
	strcpy(ptr,datas);
	//std::cout << "Memoire::blocWrite : fin\n";
	return strlen(datas);
}

//--------------------------------
//
//     blocRead
//
//--------------------------------
char *Memoire::blocRead(int id, long offset, long nb){
	//std::cout << "Memoire::blocRead : Debut (en cours  ecriture)\n";
	//std::cout << "Memoire::blocRead : id(" << id << ") ; offset(" << offset << ") ; nb(" << nb << ")\n";
	char *ptr;
	ptr = getPtrData(id);
	if (ptr == NULL){
		std::cout << "ERROR : impossible to get pointer on data structure\n";
		return NULL;
	}
	std::cout << "Memoire::blocRead : ptr(" << &ptr << ")\n";
	ptr += offset;
	//std::cout << "Memoire::blocRead : lecture dans la memoire ; taille = " << nb << "\n";
	memcpy(buffer,ptr, (size_t)nb);
	//dump(offset, nb);
	//std::cout << "Memoire::blocRead : fin\n";
	return buffer;
}

//--------------------------------
//
//     getPtrData
//
//--------------------------------
char *Memoire::getPtrData(int id){
	char *ptr;
	// retourne le pointeur sur la zone de data allouee a cet id
	structBloc tmpBloc;
	tmpBloc=getBloc(id);
	//std::cout << "Memoire::getPtrData : " << tmpBloc.datas << "\n";
	//afficheBloc(tmpBloc);
	ptr = tmpBloc.datas;
	//std::cout << "Memoire::getPtrData : " << ptr << "\n";
	return ptr;
}

//--------------------------------
//
//     garbageCollector
//
//--------------------------------
void Memoire::garbageCollector(void){
	//std::cout << "Memoire::garbageCollector => debut du garbage collector\n";

	if (monUser.getUserId() != 0){
		std::cout << "ERROR : only root user can run garbage collector\n";
		return;
	}
	long positionRead=0;
	long positionWrite=0;
	structBloc readBloc, writeBloc;
	structBloc tmpBloc;

	char commande[25];
	// creation d'un fichier temporaire pour ecrire la nouvelle liste de blocs
	char writeFileName[50];
	sprintf(writeFileName,"%s.svg",filename);

	FILE *writeFile = fopen(writeFileName,"wb+");
    if (writeFile == NULL){
    	std::cout << "ERROR : unable to open Memory File (NULL) : " << writeFileName  << "\n";
    }

	openMemoryFile();
	fseek(memoryFile,positionRead,0);
	long tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
	// affichage de l'entete
	if (tmp != tailleStructBloc){
		std::cout << "ERROR : impossible to read memory bloc list (" << tmp << ")\n";
		return;
	}
	//std::cout << "             lecture du bloc " << tmpBloc.id << "\n";
	while (tmp == tailleStructBloc){
		//std::cout << "      analyse du bloc : " << tmpBloc.id << "\n";
		if (tmpBloc.owner == -1){
			// ce bloc est a supprimer
			//std::cout << "             bloc a supprimer\n";
			// on incremente seulement le pointeur de lecture, pas celui d'ecriture
			positionRead+=tailleStructBloc;
			fseek(memoryFile,positionRead,0);
		}else{
			// on conserve ce bloc, on l'ecrit sur le fichier et on lit le bloc suivant
			// on positionne le pointeur de fichier sur l'endroit ou ecrire le bloc
			fseek(writeFile,positionWrite,0);
			// on ecrit ce bloc dans le fichier
			//std::cout << "             ecriture du bloc " << tmpBloc.id << "\n";
			fwrite(&tmpBloc,(size_t)tailleStructBloc,1,writeFile);
			// on incremente le pointeur d'ecriture de bloc 
			positionWrite+=tailleStructBloc;
			// on repositionne le pointeur de fichier sur le prochain bloc a lire
			positionRead+=tailleStructBloc;
			fseek(memoryFile,positionRead,0);
		}
		tmp = fread(&tmpBloc, 1, (size_t) tailleStructBloc, memoryFile);
		//std::cout << "             lecture du bloc " << tmpBloc.id << "\n";
	}
	fclose(writeFile);
	fclose(memoryFile);

	// on recopie la nouvelle structure de blocs dans le fichier d'origine
	sprintf(commande,"mv %s %s",writeFileName, filename);
	system(commande);
}
