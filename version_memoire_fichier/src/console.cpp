//
//  console.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <sys/select.h>
#include <stdio.h>
#include <cstring>

#include "../inc/console.hpp"
#include "../inc/os.hpp"
#include "../inc/memoire.hpp"
#include "../inc/taches.hpp"
#include "../inc/tools.hpp"


#define PARAM_SIZE	20
#define PARAM_NB	5

extern Memoire maMemoire;
extern Taches mesTaches;

char prompt[BUFF_SIZE]="Cours OS > ";
char params[PARAM_NB][PARAM_SIZE];
//char []lstCommandeInterne[]={"tsk", "kill", "mem", "dumpMem", "fillMem", "hist", "shell", "garbage", "?", "exit"};
char lstCommandeInterne[50][10]={"mem", "affBloc", "allocMem", "dump", "blocRead", "blocWrite", "nbBlocs", "tsk","kill","help", "?", "exit"};


//--------------------------------
//
//     Constructeur
//
//--------------------------------
Console::Console(){
	char saisie[BUFF_SIZE];
	char car;
	//std::cout << "Console::Console => constructeur \n";
	while (1){

		if (kbhit()){
			// un caractere a ete saisi
			car = getchar();
			std::cout << car;
		}

		/*
		std::cout << prompt;
		lireChaine(saisie,BUFF_SIZE);
		switch(analyseCommande(saisie)){
			case -1 : // exit
				return;
				break;
			default : // normal commande execution
				break;
		}*/
	}
}


//-----------------------------
//
//   lireChaine
//
//-----------------------------
void Console::lireChaine(char *chaine, int size){
	fgets(chaine, size, stdin);
	chaine[strlen(chaine) - 1] = '\0';
}

//-----------------------------
//
//   isCommandeInterne
//
//-----------------------------
int Console::isCommandeInterne(char *commande){
	char tmpCommande[BUFF_SIZE];
	strcpy (tmpCommande,commande);
	//printf("[isCommandeInterne] : <%s>\n",commande);
	int nbCmdInterne = sizeof(lstCommandeInterne) / 8;
	for (int i = 0 ; i < nbCmdInterne ; i++){
		// TODO si parametres dans la commande extraire le premier mot
		char *p=strtok(tmpCommande, " ");
		if (strcmp(lstCommandeInterne[i],p) == 0){
			return 1;
		}
	}
	return 0;
}

//-----------------------------
//
//   getParam
//
//-----------------------------
char * Console::getParam(char *chaine, int idx){
	char tmp[BUFF_SIZE];
	strcpy(tmp,chaine);
	//std::cout << "Console::getParam( : cherche param " << idx << " dans " << tmp << "\n";
	char *p = strtok(tmp, " ");
	int i=0;
	while (p != NULL){
		//std::cout << "      analyse de " << p << "\n";
		if (i == idx){
			//std::cout << "      param " << p << " OK\n";
			return p;
		}else{
			//std::cout << "      param " << p << " NOK\n";
		}
		p = strtok(NULL, " ");
		i++;
	}
	return "";
}


//-----------------------------
//
//   help
//
//-----------------------------
void Console::help(void){
	printf("+------------------------------------------------------------------------+\n");
	printf("| Liste des commandes internes disponibles                               |\n");	
	printf("+----------------------+-------------------------------------------------+\n");
	printf("| tsk                  | liste des taches                                |\n");
	printf("| kill <id|nom>        | tue la tache <id|nom>                           |\n");
	printf("| mem                  | description de la memoire                       |\n");
	printf("| affBloc id           | description d'un bloc memoire                   |\n");
	printf("| allocMem  <size>     | allocation d'un bloc memoire de taille size     |\n");
	printf("| dump deb n           | dump n elements de memoire depuis deb           |\n");
	printf("| blocRead id deb n    | lit n elements du programme id depuis deb       |\n");
	printf("| blocWrite id deb n   | ecrit n elements du programme id depuis deb     |\n");
	printf("| nbBlocs              | nombre de blocs memoire definis                 |\n");
	//printf("| fillMem deb n car    | remplis memoire avec n car depuis deb           |\n");
	//printf("| storeMem deb text    | remplis memoire avec text depuis deb            |\n");
	//printf("| hist                 | historique des commandes                        |\n");
	//printf("| ls                   | liste des taches externes                       |\n");
	//printf("| shell                | lance un shell dans une nouvelle fenetre        |\n");
	//printf("| garbage              | nettoyage de la memoire                         |\n");
	printf("| help                 | cet ecran d'aide                                |\n");
	printf("| ?                    | cet ecran d'aide                                |\n");
	printf("| exit                 | quitte la console                               |\n");
	printf("+----------------------+-------------------------------------------------+\n");
}


//-----------------------------
//
//   analyseCommande
//
//-----------------------------
int Console::analyseCommande(char *chaine){


	char param[100];
	char param1[100];
	char param2[100];
	
	if (isCommandeInterne(chaine)){
		//std::cout << "analyseCommande : chaine = <" << chaine << ">\n";
		if (strcmp(chaine,"exit") == 0){
			return -1;
		} else if (strncmp(chaine,"allocMem", 8) == 0){
			char param[10];
			strcpy(param, getParam(chaine, 1));
			if (strcmp(param,"") == 0){
				std::cout << "ERROR : manque parametre\n";
				return 0;
			}
	 		maMemoire.alloueBloc(atol(param), BLOC_TYPE_MEM);
		} else if (strncmp(chaine,"dump",4) == 0){
			strcpy(param, getParam(chaine, 1));
			strcpy(param1, getParam(chaine, 2));
			//std::cout << "Console::analyseCommande : param = " << param << "; param1 = " << param1 << "\n";
			maMemoire.display(atol(param),atol(param1));
		} else if (strncmp(chaine,"blocRead",8) == 0){
			strcpy(param, getParam(chaine, 1));
			strcpy(param1, getParam(chaine, 2));
			strcpy(param2, getParam(chaine, 3));
			maMemoire.blocRead(atoi(param),atol(param1),atol(param2));
		} else if (strncmp(chaine,"blocWrite",9) == 0){
			strcpy(param, getParam(chaine, 1));
			strcpy(param1, getParam(chaine, 2));
			strcpy(param2, getParam(chaine, 3));
			//std::cout << "Console::analyseCommande : param = " << param << "; param1 = " << param1 << "\n";
			maMemoire.blocWrite(atoi(param),atol(param1),param2);
		} else if (strcmp(chaine,"nbBlocs") == 0){
			std::cout << "nb blocs defined : " << maMemoire.nbBlocs() << "\n";
		} else if (strcmp(chaine,"help") == 0){
			help();
		} else if (strcmp(chaine,"?") == 0){
			help();
		} else if (strcmp(chaine, "mem") == 0){
			maMemoire.listeBlocs();
		} else if (strncmp(chaine, "affBloc",7) == 0){
			strcpy(param, getParam(chaine, 1));
			maMemoire.afficheBloc(maMemoire.getBloc(atoi(param)));
		} else if (strcmp(chaine, "tsk") == 0){
			mesTaches.listeTaches();
		} else if (strncmp(chaine, "kill",4) == 0){
			int result;
			strcpy(param, getParam(chaine, 1));
			if (atol(param) != 0){
				result = mesTaches.kill(atol(param));
			}else{
				result = mesTaches.kill(param);
			}
			if (result == -1){
				std::cout << "ERROR : Impossible to kill " << param << "\n";
			}
		}
	}else{
		// ce n'est pas une commmande interne
		int tskId = mesTaches.lance(chaine);
		if (tskId == -1){
			std::cout << "ERROR : Impossible to launch " << chaine << "\n";
		}
	}
	return 0;
}




