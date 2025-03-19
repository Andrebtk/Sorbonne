(select nom, prenom
from Athlete
where lower(pays)='suisse')

INTERSECT 

(select nomAth, prenomAth
from rangepreuve
where rang is NULL AND lower(sport)='biathlon')