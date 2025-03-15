select DISTINCT a.nomAth, a.prenomAth
from Athlete a, rangIndividuel ri, AthletesEquipe ae
where ri.aid = a.aid AND ae.aid=a.aid