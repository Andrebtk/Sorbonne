#! /bin/bash

sum=""
while true; 
do
    echo -n Saisissez un nombre ou 'q' pour quitter : 
    read input

    if test $input = 'q'; 
    then
        break
    fi
    echo Vous avez ajouté $input à la somme
    sum="$sum $input"

done

./somme $sum
