select ae1.eqid, a1.nomAth, a2.nomAth
from Athlete a1, Athlete a2, AthletesEquipe ae1, AthletesEquipe ae2
where a1.aid <> a2.aid AND ae1.aid = a1.aid AND ae2.aid = a2.aid AND ae1.eqid = ae2.eqid 
    AND NOT EXISTS (
        select *
        from athlete a3, AthletesEquipe ae3
        where a3.aid=ae3.aid AND ae3.eqid=ae1.eqid AND a3.aid <>a1.aid AND a3.aid <> a2.aid
    )