select a.nom, count(*)
from TourneAutour ta, astre a 
where a.ida = ta.ida2
group by ta.ida2