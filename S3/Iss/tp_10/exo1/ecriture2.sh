#! /bin/bash

if [ $# -lt 1 ]; then
	echo Il faut au moins un parametre
	exit 1
fi

for elem in "$@"; do
	semcmd lock myLock	
	if [ ! -e $elem ]; then
		sleep 1
		echo premier $$ > "$elem"
	else 
		echo suivant $$ >> "$elem"
	fi
	semcmd unlock myLock
done
