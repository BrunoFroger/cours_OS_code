#
#  makefile
#  OS et testsOS
#
#  Created by Bruno FROGER on 20/11/2017.
#  Copyright © 2017 Bruno FROGER. All rights reserved.
#


CC=g++
CCFLAGS=-Wall -c -o $@

OBJ=obj/Memoire.o obj/BlocMemoire.o obj/memPartagee.o obj/console.o
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
obj/os.o: src/os.cpp\
	inc/Memoire.hpp
	$(CC) $(CCFLAGS) src/os.cpp 

obj/test.o: src/test.cpp\
	inc/Memoire.hpp\
	inc/os.hpp
	$(CC) $(CCFLAGS) src/test.cpp 

obj/shellOs.o: src/shellOs.cpp\
	inc/console.hpp\
	inc/os.hpp
	$(CC) $(CCFLAGS) src/shellOs.cpp 

#
# compilatoindes modules communs
#
obj/Memoire.o: src/Memoire.cpp\
	inc/Memoire.hpp
	$(CC) $(CCFLAGS) src/Memoire.cpp 

obj/BlocMemoire.o: src/BlocMemoire.cpp\
	inc/Memoire.hpp\
	inc/os.hpp
	$(CC) $(CCFLAGS) src/BlocMemoire.cpp 

obj/memPartagee.o: src/memPartagee.cpp\
	inc/memPartagee.hpp\
	inc/os.hpp
	$(CC) $(CCFLAGS) src/memPartagee.cpp 

obj/console.o: src/console.cpp\
	inc/memPartagee.hpp\
	inc/console.hpp
	$(CC) $(CCFLAGS) src/console.cpp 

#
#nettoyage
#
clean:
	rm obj/* bin/*