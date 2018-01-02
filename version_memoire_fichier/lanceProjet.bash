#!/bin/bash


clear
make

export ret=$?

#echo "retour = " $ret
if [ $ret -eq 0 ]; then
	clear
	if [ "$1" == "" ]; then
		echo "manque nom de l'executable a lancer"
		exit 
	fi
	bin/$1
else
	echo "erreurs de compilation"
fi