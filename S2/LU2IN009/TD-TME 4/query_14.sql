(select nomAth, prenomAth 
from rangEpreuve
where rang >=3)

INTERSECT 

(select nom, prenom
from Athlete
where datediff(day, dateNaissance, current_date) < (30*365)
)