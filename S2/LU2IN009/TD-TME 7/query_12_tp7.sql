select c.nom, max(rayon)
from Astre a, categorie c
where a.idc = c.idc
group by a.idc
order by count(*) DESC