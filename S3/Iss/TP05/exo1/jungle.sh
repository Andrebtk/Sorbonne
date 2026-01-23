read -p "[1] VF [2] VO: " choix_lang

IFS="," 
while read animal son_fr son_en; do 
    if [ $choix_lang -eq 1 ]; then
        cowsay -f $animal $son_fr
    fi
    if [ $choix_lang -eq 2 ]; then
        cowsay -f $animal $son_en
    fi
done < $1