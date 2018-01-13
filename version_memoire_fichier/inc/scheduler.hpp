//
//  scheduler.hpp
//  OS
//
//  Created by Bruno FROGER on 03/01/2018.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include "../inc/taches.hpp"

#ifndef scheduler_hpp
#define scheduler_hpp

#define MAX_PRIORITY_LEVEL	128
#define STD_PRIORITY_LEVEL	64

class Scheduler{
private:
	int courantPriorityLevel;
	int normalPriorityLevel;

public:
	Scheduler();
	void loop(void);
	void increasePriorityLevel(void);
	void decreasePriorityLevel(void);
	void resetPriorityLevel(void);
};

#endif
