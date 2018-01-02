//
//  tools.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctime>
#include <cstring>
#include "../inc/tools.hpp"


/*
void syslog_print(int level, const char *format, ...)
{
  va_list args;
  va_start(args, format);
 
  openlog("OS_LOG", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
  char tmp[100];
  sprintf(tmp,format,args);
  printf("%s",tmp);
  vsyslog(level, format, args);
  closelog();
 
  va_end(args);
}
*/

void log_print(int level, const char *format, ...)
{
  va_list args;
  va_start(args, format);
 
  FILE *fic = fopen("os.log", "a+");
  char tmp[500];
  time_t rawtime;
  time(&rawtime);
  char entete[200];
  char result[500];

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
  sprintf(tmp,format,args);
  sprintf(result, "%s => %s\n",entete, tmp);
  //printf("%s",result);

  fwrite(result, 1, strlen(result), fic);
  fclose(fic);
 
  va_end(args);
}


#include <sys/select.h>
#include <stdio.h>

/*
int kbhit(void) {

    struct timeval tv;
    fd_set fd;
   
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fd);
    FD_SET(0, &fd);
    if(-1 != select(1, &fd, NULL, NULL, &tv)) {
        if(FD_ISSET(0, &fd)) {
            return 1;
        }
    }
    return 0;
}
*/

int kbhit(void)
{
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


int usleep(int milliseconds){
	int milliseconds=10;
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
    return 0;
}
