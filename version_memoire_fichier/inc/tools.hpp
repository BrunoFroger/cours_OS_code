//
//  Tools.hpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//

#include <stdarg.h>
#include <syslog.h>


#ifndef tools_hpp
#define tools_hpp


#define DEBUG(format, ...) log_print(LOG_DEBUG, format, ##__VA_ARGS__)
#define INFO(format, ...)  log_print(LOG_INFO, format, ##__VA_ARGS__)
#define WARN(format, ...)  log_print(LOG_WARNING, format, ##__VA_ARGS__)
#define ERROR(format, ...) log_print(LOG_ERR, format, ##__VA_ARGS__)


#endif

int kbhit(void);
void log_print(int level, const char *format, ...);
int usleep(int milliseconds);
