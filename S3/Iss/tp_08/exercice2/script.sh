for lettre in {A..Z}; do
    grep -E "^$lettre" dico.txt > "dico/$lettre.txt" &
done


