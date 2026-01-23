#!/bin/bash

function usage() {
    echo "Usage : $0 <fichier>"
    exit 1
}

if [ $# -ne 1 ]; then
    usage 
fi

if test -r $1; then
    echo "Bon fichier" 
else 
    usage
fi

# Question 3:
nbConnexion=$(cat $1 | head -n -2 | wc -l)
echo "Nombre d'entées: $nbConnexion"

# Question 4:
lastConnexion=$(cat $1 | head -n 1 | cut -d ' ' -f 1)
if [ $lastConnexion = $(whoami) ]; then 
    echo "Vous êtes le dernier à vous être connecté à la machine"
fi

# Question 5: 
nbConnexionUsr=$(cat $1 | grep $(whoami) | wc -l)
echo "nbConnexion de l'utilisateur: $nbConnexionUsr"

# Question 6:
nbConnexionUtilisateurUnique=$(cat $1 | cut -d ' ' -f  1 | sort | uniq | head -n -5 | wc -l)
echo "nbConnexionUtilisateur au moins 1 fois: $nbConnexionUtilisateurUnique"

# Question 7:
nbMachineDistante=$(cat $1 | cut -c 61- | sort | uniq | grep -v 0.0.0.0 | sort | wc -l)
echo "Nombre de machine distante : $nbMachineDistante"

# Question 8:
cat "$1" | grep -v '0.0.0.0' | while read -r line; do
    user=$(echo "$line" | cut -d ' ' -f 1)
    machine=$(echo "$line" | cut -c 61-)

    # Affiche l'utilisateur et la machine
    if [ ! -z "$machine" ]; then
        echo "Utilisateur: $user, Machine: $machine"
    fi
done | sort | uniq

