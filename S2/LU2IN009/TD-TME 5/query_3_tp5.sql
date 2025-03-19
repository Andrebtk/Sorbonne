select DISTINCT a.nomath, a.prenomAth
from Athlete a, equipe e, pays p, athletesEquipe ae
Where p.nomp='France' AND p.codepays=e.codepays 
    AND a.aid = ae.aid and ae.eqid=e.eqid