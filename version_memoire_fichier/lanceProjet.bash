#!/bin/bash


clear
make

export ret=$?

#echo "retour = " $ret
if [ $ret -eq 0 ]; then
	clear
	bin/$1
else
	echo "erreurs de compilation"
fi