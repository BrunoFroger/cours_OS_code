//
//  tools.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <cstring>
#include "../inc/tools.hpp"

//--------------------------------
//
//     log_print
//
//--------------------------------
void log_print(int level, const char *format, ...){
	va_list args;
	va_start(args, format);

	FILE *fic = fopen("os.log", "a+");
	char tmp[500]="";
	time_t rawtime;
	time(&rawtime);
	char entete[200]="";
	char result[500]="";
	int i=0;
	int idx=0;
	char v[30]="";
	int n;

	strcpy(entete, ctime(&rawtime));
	entete[strlen(entete)-1]='\0';

	switch (level){
		case LOG_INFO :
			strcat(entete, " : INFO : ");
			break;
		case LOG_DEBUG :
			strcat(entete, " : DEBUG : ");
			break;
		case LOG_WARNING :
			strcat(entete, " : WARNING : ");
			break;
		case LOG_ERR :
			strcat(entete, " : ERROR : ");
			break;
		default:
			std::cout << "ERROR : invalid log level \n";
			break;
	}

	while(*(format+i)!='\0'){
		//car=*(format+i);
		switch(*(format+i)){
			case '%':
				i++;
				if(*(format+i)=='c'){
					tmp[idx++]=va_arg(args,int);
				}

				if(*(format+i)=='d'){
					n=va_arg(args,int);
					sprintf(v,"%d",n);
					strcat(tmp,v);
					idx+=strlen(v);
				}
				if(*(format+i)=='s'){
					strcpy(v,va_arg(args,char *));
					strcat(tmp,v);
					idx+=strlen(v);
				}
				break;

			default :
				tmp[idx++]=*(format+i); 
				break;
		}
		i++;
	}
	tmp[idx]='\0';
	sprintf(result, "%s => %s\n",entete, tmp);
	//printf("%s",result);

	fwrite(result, 1, strlen(result), fic);
	fclose(fic);

	va_end(args);
}

//--------------------------------
//
//     kbhit
//
//--------------------------------
int kbhit(void){
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

//--------------------------------
//
//     usleep
//
//--------------------------------
int usleep(int milliseconds){
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
    return 0;
}
