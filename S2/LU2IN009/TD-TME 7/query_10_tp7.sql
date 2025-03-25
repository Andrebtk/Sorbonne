select a.nom, ob.dateObs, avg(ob.valObs)
from Observation ob, astre a
where a.ida = ob.ida
group by ob.ida, ob.dateobs