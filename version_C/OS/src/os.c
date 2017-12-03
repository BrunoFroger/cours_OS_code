

#include "../inc/tache.h"
#include "../inc/mem.h"

int main(void){

	initMem();
	createTache("Monitor", PRIO_INIT, &(monitor));
	scheduler();
}