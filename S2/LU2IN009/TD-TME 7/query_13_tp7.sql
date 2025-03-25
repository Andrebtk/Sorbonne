select a1.idc, a1.nom, a1.rayon
from Astre a1
where rayon = (select max(a2.rayon)
                from astre a2
                where a1.idc = a2.idc)