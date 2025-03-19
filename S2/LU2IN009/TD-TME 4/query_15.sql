(select nom, prenom, DAY_OF_MONTH(datenaissance), MONTH(datenaissance)
from athlete)
INTERSECT 
(select nomAth, prenomAth, DAY_OF_MONTH(datefin), MONTH(datefin)
from rangEpreuve)