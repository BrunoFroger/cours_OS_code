#!/bin/bash


echo "lancement du projet OS"

export SRC="src/BlocMemoire.cpp src/console.cpp src/Memoire.cpp src/memPartagee.cpp"
export INC="inc/os.hpp inc/console.hpp inc/Memoire.hpp inc/memPartagee.hpp"
export MAINS="src/shellOs.cpp src/test.cpp src/os.cpp "
export TOOLS="build.bash lanceProjet.bash todo.txt makefile"

subl -n $TOOLS
subl -n $SRC
subl -n $INC
subl -n $MAINS
