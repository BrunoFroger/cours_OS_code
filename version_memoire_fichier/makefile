#
#  makefile
#  OS et testsOS
#
#  Created by Bruno FROGER on 20/11/2017.
#  Copyright © 2017 Bruno FROGER. All rights reserved.
#


CC=c++
CCFLAGS=-Wall -c -o $@

OBJ=obj/memoire.o obj/console.o obj/taches.o obj/tools.o
OBJ_OS=$(OBJ) obj/os.o
OBJ_TST=$(OBJ) obj/test.o
OBJ_SH=$(OBJ) obj/shellOs.o


all: bin/os\
	bin/test\
	bin/shellOs

#
# generation des executables
#
bin/os: $(OBJ_OS)
	$(CC) $(OBJ_OS) -o $@

bin/test: $(OBJ_TST)
	$(CC) $(OBJ_TST) -o $@

bin/shellOs: $(OBJ_SH)
	$(CC) $(OBJ_SH) -o $@

#
# compilatoin des sources specifiques des executables
#
obj/os.o: src/os.cpp
	$(CC) $(CCFLAGS) src/os.cpp 

obj/test.o: src/test.cpp
	$(CC) $(CCFLAGS) src/test.cpp 

obj/shellOs.o: src/shellOs.cpp
	$(CC) $(CCFLAGS) src/shellOs.cpp 

#
# compilatoin des modules communs
#
obj/memoire.o: src/memoire.cpp\
	inc/memoire.hpp
	$(CC) $(CCFLAGS) src/memoire.cpp 

obj/console.o: src/console.cpp\
	inc/console.hpp
	$(CC) $(CCFLAGS) src/console.cpp 
 
obj/taches.o: src/taches.cpp\
	inc/taches.hpp
	$(CC) $(CCFLAGS) src/taches.cpp 

obj/tools.o: src/tools.cpp\
	inc/tools.hpp
	$(CC) $(CCFLAGS) src/tools.cpp 

#
#nettoyage
#
clean:
	rm obj/* bin/*