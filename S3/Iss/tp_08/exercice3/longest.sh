[ $# -ne 1 ] && echo "usage: $0 <fichier>" && exit -1


motL=""
motMax=0
while read mot; do
    if [ ${#mot} -gt $motMax ]; then 
        motL=$mot
        motMax=${#mot}
    fi
done < $1

echo $motL > $1.tmp