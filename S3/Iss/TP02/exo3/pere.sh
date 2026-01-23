#! /bin/bash
echo "mon PID: $$"

for n in {0..9}; do # Fait une boucle de 0 à 9 et, à chaque itération, exécute fils.sh
    ./fils.sh
done