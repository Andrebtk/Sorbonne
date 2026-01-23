select a.nomAth, a.prenomAth
from Athlete a
where a.aid NOT IN (select ri.aid
                    from rangIndividuel ri
                    where ri.rang IS NULL)