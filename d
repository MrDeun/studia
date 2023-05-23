#!/bin/bash
if [ -f "$1" ]
then
	echo -e "Plik $1 istnieje \n czy edytowac?"
	read answer
	if [ "$answer" = "tak"]
	then
		nano $1
	else cat $1 | less
	fi
else
	echo "Brak pliku"
fi
