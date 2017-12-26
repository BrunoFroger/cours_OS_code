//
//  tools.cpp
//  OS
//
//  Created by Bruno FROGER on 20/11/2017.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//



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

