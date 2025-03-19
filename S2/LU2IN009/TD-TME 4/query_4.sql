select prenom, nom, pays
from Athlete
where prenom='Suk-Hee' AND nom='SHIM' 
UNION (
    select prenom, nom, pays
    from Athlete
    where prenom='Kamil' and nom='STOCH'
)