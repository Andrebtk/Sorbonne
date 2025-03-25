select nom, rayon
from astre
where rayon = (select max(rayon)
                from astre)