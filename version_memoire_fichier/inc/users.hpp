//
//  users.cpp
//  OS
//
//  Created by Bruno FROGER on 03/01/2018.
//  Copyright © 2017 Bruno FROGER. All rights reserved.
//


#ifndef users_hpp
#define users_hpp

class Users{
private:
	int userId;
	char userName[50];
	char filename[50];
	FILE * memoryFile;
	int tailleStructBloc;
	void openMemoryFile(void);

public:
	Users();
	void setName(char *name);
	char *getName(void);
	int getUserId(void);
	void init(char *nomFichier, int id, char *userName);
	int getLastUserId(void);
	int getNewUserId(void);
	void listeUsers(void);
	void kill(void);
	int nbUsers(void);
};

#endif