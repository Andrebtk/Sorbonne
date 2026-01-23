echo "Les albums recommandés des Beatles sont :" 
ls 1001_Albums_You_Must_Hear_Before_You_Die/*-[A-Za-z]-*.flac

count=0
total_count=0;

for album in 1001_Albums_You_Must_Hear_Before_You_Die/*.flac
do
	filename=${album##*/}
	filename=${filename%.flac}
	total_count=$((total_count + ${#filename}))
	count=$((count + 1))
done

echo "Il y a $count albums"  #1065
echo "La moyenne des tailles des noms de fichiers de ces albums est" $(($total_count/$count))


for annee in {1995..2016}
do 
	echo -n "$annee: "
	for x in 1001_Albums_You_Must_Hear_Before_You_Die/*-*-$annee.flac
	do 
		echo -n "x"
	done
	echo
done

