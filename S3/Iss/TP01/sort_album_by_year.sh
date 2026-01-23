for annee in {1995..2016}
do 
	mkdir $annee
	for x in 1001_Albums_You_Must_Hear_Before_You_Die/*-*-$annee.flac
	do 
		cp $x $annee
	done
done