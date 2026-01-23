select a.nom
from astre a, tourneAutour ta
where a.ida = ta.ida2
group by ida
having count(*) >= 2