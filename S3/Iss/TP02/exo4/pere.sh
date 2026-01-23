#! /bin/bash

# Si aucun paramètre n'est fourni, on termine le script
if test $# -eq 0; then
    echo "Il manque un paramètre"
    echo "Usage : ./pere.sh <nb_fils>"
    exit 
fi
echo "je suis: $$"

# Compteur initialisé à 0
compteur=0

# Boucle tant que le compteur n'est pas égal au premier argument
while [ $compteur -ne $1 ]; do 
    # Incrémente de 1 le compteur
    compteur=$((compteur+1)) 
    # Affichage
    echo -n "Fils $compteur: "; ./fils.sh
done