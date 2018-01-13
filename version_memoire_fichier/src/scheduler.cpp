//
//  scheduler.cpp
//  OS
//
//  Created by Bruno FROGER on 08/01/2018.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#include "../inc/Memoire.hpp"
#include "../inc/taches.hpp"
#include "../inc/scheduler.hpp"


extern Memoire maMemoire;
extern Taches mesTaches;

//--------------------------------
//
//     Constructeur
//
//--------------------------------
Scheduler::Scheduler(){
    //std::cout << "Users::Users : constructeur\n";
    normalPriorityLevel=STD_PRIORITY_LEVEL;

}

//--------------------------------
//
//     decreasePriorityLevel
//
//--------------------------------
void Scheduler::decreasePriorityLevel(void){
	courantPriorityLevel--;
	if (courantPriorityLevel <= 0){
		courantPriorityLevel = 0;
	}
}

//--------------------------------
//
//     increasePriorityLevel
//
//--------------------------------
void Scheduler::increasePriorityLevel(void){
	courantPriorityLevel++;
	if (courantPriorityLevel >= MAX_PRIORITY_LEVEL){
		courantPriorityLevel = MAX_PRIORITY_LEVEL;
	}
}

//--------------------------------
//
//     resetPriorityLevel
//
//--------------------------------
void Scheduler::resetPriorityLevel(void){
	courantPriorityLevel = normalPriorityLevel;
}

//--------------------------------
//
//     init
//
//--------------------------------
void Scheduler::loop(void){
	structTache courantTask,newTask;
	
	courantTask.status = TASK_NA;
	newTask.status = TASK_NA;
	while (1){
		// boucle permettant de gerer les changemetns de contextes
		newTask = mesTaches.getNextActiveTask(courantPriorityLevel);
		if (newTask.status != TASK_NA){
			// il y a une nouvelle tache
			if (newTask.priority >= courantPriorityLevel){
				// on verifie le niveau de priorite de cette nouvelle tache
			}
			mesTaches.pushActiveTask(courantTask);
		}else{
			// plus de taches actives a ce niveau de priorite
			// on l'abaisse pour gerer les taches moins prioritaires
			decreasePriorityLevel();
		}
	}
}
