//
//  console.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../inc/console.hpp"
#include "../inc/memPartagee.hpp"
#include "../inc/os.hpp"


#define PARAM_SIZE	20
#define PARAM_NB	5


char prompt[BUFF_SIZE]="Cours OS > ";
char params[PARAM_NB][PARAM_SIZE];
//char []lstCommandeInterne[]={"tsk", "kill", "mem", "dumpMem", "fillMem", "hist", "shell", "garbage", "?", "exit"};
char lstCommandeInterne[10][10]={"help", "exit", "mem"};

extern BlocMemoire *firstBlocMemoire;
extern MemPartagee memPartagee;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Console::Console(){
	char saisie[BUFF_SIZE];
    std::cout << "Console\n";

	firstBlocMemoire = memPartagee.getFirstBlocMemoire();
	std::cout << "Console : firstBlocMemoire : " << firstBlocMemoire << "\n";
	if (firstBlocMemoire == NULL){
		std::cout << "ERROR : unable to access to list of memory blocs \n";
		return;
	}
	std::cout << "Console : aff data partagee\n";
	//firstBlocMemoire->affBlocDetail();
	std::cout << "Console \n";
	while (1){
		std::cout << prompt;
		lireChaine(saisie,BUFF_SIZE);
		analyseCommande(saisie);
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
//   help
//
//-----------------------------
void Console::help(void){
	printf("+----------------------------------------------------------------+\n");
	printf("| Liste des commandes internes disponibles                       |\n");	
	printf("+-------------------+--------------------------------------------+\n");
	//printf("| tsk               | liste des taches                           |\n");
	//printf("| kill <id>         | tue la tache <id>                          |\n");
	printf("| mem  <1|2>        | description de la memoire (1:free, 2:used) |\n");
	//printf("| dumpMem  deb n    | dump de n elements de memoire depuis deb   |\n");
	//printf("| fillMem deb n car | remplis memoire avec n car depuis deb      |\n");
	//printf("| storeMem deb text | remplis memoire avec text depuis deb       |\n");
	//printf("| hist              | historique des commandes                   |\n");
	//printf("| ls                | liste des taches externes                  |\n");
	//printf("| shell             | lance un shell dans une nouvelle fenetre   |\n");
	//printf("| garbage           | nettoyage de la memoire                    |\n");
	printf("| help              | cette ecran d'aide                         |\n");
	printf("| ?                 | cette ecran d'aide                         |\n");
	printf("| exit              | quitte la console                          |\n");
	printf("+-------------------+--------------------------------------------+\n");
}

//-----------------------------
//
//   analyseCommande
//
//-----------------------------
void Console::analyseCommande(char *chaine){

	std::cout << "analyseCommande : chaine = <" << chaine << ">\n";
	if (strcmp(chaine,"exit") == 0){
		exit(0);
	} else if (strcmp(chaine,"help") == 0){
		help();
	} else if (strcmp(chaine,"?") == 0){
		help();
	} else if (strcmp(chaine, "mem") == 0){
		do{ 
			firstBlocMemoire->affBlocs();
			std::cout << "Press enter to refresh (or q to quit)\n";
		} while (std::cin.get() != 'q');
	}
}




