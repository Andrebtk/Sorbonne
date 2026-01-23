(select nomAth,prenomAth
from rangEpreuve
where lower(categorie) = 'femmes')

INTERSECT (
select nom, prenom
from Athlete
where pays='France'

)