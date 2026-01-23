#! /bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <Dossier>"
    exit 1
fi

nom=""
nomTaille=0

for i in $1/*; do
    taille=$(wc -m < "$i")
    if test $taille -gt $nomTaille; then
        nomTaille=$taille
        nom=$i
    fi
done

echo $nom 