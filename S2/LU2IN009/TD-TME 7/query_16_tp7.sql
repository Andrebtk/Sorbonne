select a.nom
from Observation ob, Astre a
where ob.ida = a.ida
group by ob.ida
having count(*) = 2