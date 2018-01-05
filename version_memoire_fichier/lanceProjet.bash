#!/bin/bash


if [ "$1" == "" ]; then
	echo "manque nom de l'executable a lancer"
	exit 
fi
clear
make bin/$1

export ret=$?

#echo "retour = " $ret
if [ $ret -eq 0 ]; then
	clear
	bin/$1 $2
else
	echo "erreurs de compilation"
fi