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
#include <unistd.h>
#include <time.h>

#include "../inc/console.hpp"
#include "../inc/os.hpp"
#include "../inc/memoire.hpp"
#include "../inc/taches.hpp"
#include "../inc/tools.hpp"
#include "../inc/users.hpp"


#define PARAM_SIZE	20
#define PARAM_NB	5

char prompt[BUFF_SIZE];
char params[PARAM_NB][PARAM_SIZE];
char lstCommandeInterne[50][10]={"hist", "gc", "log", "whoami", "mem", "users", "affBloc", "allocMem", "dump", "blocRead", "blocWrite", "nbBlocs", "tsk","kill","help", "?", "exit"};
char historique[CMD_HISTORY_SIZE][BUFF_SIZE];
int ptrHistorique=0;

extern Memoire maMemoire;
extern Taches mesTaches;
extern Users monUser;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Console::Console(){
	char saisie[BUFF_SIZE];
	//std::cout << "Console::Console => constructeur \n";
	char tmp[100];
	char userName[100];
	sprintf(userName, "%s", monUser.getName());
	sprintf(tmp, "%s", "console");
	
	INFO("Connexion du user %s", userName);
	mesTaches.creeBlocTache(tmp, 100, tmp);

	//std::cout << "Connexion du userId " << userId << "\n";
	sprintf(prompt, "Cours OS (user %s) > ",userName);
	sprintf(saisie,"");
	while (1){
		printf("\r%s%s",prompt,saisie) ;
		lireChaine(saisie,BUFF_SIZE);
		//std::cout << "boucle principale de la console : chaine saisie : (" << saisie << ")\n";
		switch(analyseCommande(saisie)){
			case -1 : // exit
				monUser.kill();
				INFO("Deconnexion du user %s", userName);
				return;
				break;
			default : // normal commande execution
				sprintf(saisie,"");
				break;
		}
		//std::cout << "fin de la boucle principale de la console\n";
	}
}

//-----------------------------
//
//   AffHistoryCommandes
//
//-----------------------------
void Console::AffHistoryCommandes(void){
	int index=ptrHistorique+1;
	int cpt=0;;
	do{
		printf("%3d : %s\n",cpt++, historique[index++]);
		if (index > CMD_HISTORY_SIZE){
			index = 0;
		}
	}while (index != ptrHistorique);
}


//-----------------------------
//
//   historiseCommande
//
//-----------------------------
void Console::historiseCommande(char *chaine){
	ptrHistorique++;
	strcpy(historique[ptrHistorique],chaine);
	if (ptrHistorique >= CMD_HISTORY_SIZE) {
		ptrHistorique=0;
	}
}

//-----------------------------
//
//   lireChaine
//
//-----------------------------
void Console::lireChaine(char *chaine, int size){

	std::cout << std::flush;
	strcpy(chaine,"");
	char car, car1;
	int idx=0;
	while (1){
		if (kbhit()){
			car = getchar();
			std::cout << std::flush;
			//printf("code de touche saisie %d(0x%02x) \n",car,car);
			switch (car){
				case 0x0a: // return
					// validation de la commande par return
					//std::cout << "validation de la commande " << chaine << "\n";
					// on stocke la commande dans l'historique
					historiseCommande(chaine);
					return;
					break;;
				case 0x1b:	// ESC
					// saisie d'un caractere special (esc + ...)
					//printf("touche speciale saisie (esc)\n");
					car1 = getchar();
					if (car1 == 0x5b){
						car1 = getchar();
						// on traite la gestion des fleches
						switch(car1){
							case 65: 
								// fleche vers le haut
								printf("touche fleche haut \n");
								break;
							case 66: 
								// fleche vers le bas
								printf("touche fleche bas \n");
								break;
							case 67: 
								// fleche vers la droite
								printf("touche fleche droite \n");
								break;
							case 68: 
								// fleche vers la gauche
								printf("touche fleche gauche \n");
								break;
							default:
								printf("code de touche inconnu %d(0x%02x) \n",car1,car1);
						}
					}
					break;;
				default:
					// autre caractere, on l'ajoute a la chaine
					//std::cout << car;
					chaine[idx++]=car;
					chaine[idx]='\0';
					break;
			}
		}

		usleep(10);
	}
	std::cout << std::flush;
}

//-----------------------------
//
//   isCommandeInterne
//
//-----------------------------
int Console::isCommandeInterne(char *commande){
	if (strlen(commande) == 0) return 0;
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
	printf("| hist                 | historique des commandes                        |\n");
	printf("| tsk                  | liste des taches                                |\n");
	printf("| gc                   | garbage collector                               |\n");
	printf("| whoami               | affiche le userId                               |\n");
	printf("| kill <id|nom>        | tue la tache <id|nom>                           |\n");
	printf("| mem                  | description de la memoire                       |\n");
	printf("| affBloc id           | description d'un bloc memoire                   |\n");
	printf("| allocMem  <size>     | allocation d'un bloc memoire de taille size     |\n");
	printf("| dump deb n           | dump n elements de memoire depuis deb           |\n");
	printf("| blocRead id deb n    | lit n elements du programme id depuis deb       |\n");
	printf("| blocWrite id deb n   | ecrit n elements du programme id depuis deb     |\n");
	printf("| nbBlocs              | nombre de blocs memoire definis                 |\n");
	printf("| log                  | envoi un message dans le fichier de log         |\n");
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
		//std::cout << "analyseCommande : chaine = <" << chaine << "> (" << strlen(chaine) << ")\n";
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
		} else if (strcmp(chaine,"hist") == 0){
			AffHistoryCommandes();
		} else if (strcmp(chaine,"?") == 0){
			help();
		} else if (strcmp(chaine, "mem") == 0){
			maMemoire.listeBlocs();
		} else if (strcmp(chaine, "gc") == 0){
			maMemoire.garbageCollector();
		} else if (strncmp(chaine, "affBloc",7) == 0){
			strcpy(param, getParam(chaine, 1));
			maMemoire.afficheBloc(maMemoire.getBloc(atoi(param)));
		} else if (strcmp(chaine, "tsk") == 0){
			mesTaches.listeTaches();
		} else if (strcmp(chaine, "whoami") == 0){
			std::cout << "userId = " << monUser.getUserId() << "; name = " << monUser.getName() << "\n";
		} else if (strcmp(chaine, "users") == 0){
			monUser.listeUsers();
			printf("fin de listeUsers\n");
			std::cout << "Console::analyseCommande => fin d'affichage de la liste des users \n";
		} else if (strncmp(chaine, "log",3) == 0){
			strcpy(param, getParam(chaine, 1));
			INFO(param);
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
		//std::cout << "Console::analyseCommande => fin d'execution d'une commande interne \n";
	}else{
		// ce n'est pas une commmande interne
		if (strlen(chaine) == 0){
			// pas de commande saisie
			return 0;
		}
		int tskId = mesTaches.lance(chaine);
		if (tskId == -1){
			std::cout << "ERROR : Impossible to launch " << chaine << "\n";
		}
		//std::cout << "Console::analyseCommande => fin d'execution d'une commande externe \n";
	}
	//std::cout << "Console::analyseCommande => fin d'analyse de commande\n";
	return 0;
}




