(select nom, prenom
from Athlete
where lower(pays)='france')

INTERSECT

(select nomAth, prenomAth
from rangepreuve
where rang in (1,2,3))