[ $# -ne 1 ] && echo "usage: $0 <dossier>" && exit -1
[ ! -d $1 ] && echo "$1 n'est pas un dossier" && exit -1

for fichier in $(ls $1); do 
    bash longest.sh $1/$fichier &
done

wait

for file in $(ls $1 | grep ".tmp"); do 
    cat dico/$file >> final.txt &
done

wait 

bash longest.sh final.txt
cat final.txt.tmp

rm *.tmp