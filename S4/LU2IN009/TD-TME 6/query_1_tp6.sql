select a.nomAth, a.prenomAth
from Athlete a
where a.aid = ANY (
        select ri.aid
        from RangIndividuel ri
    ) 
    AND a.aid = ANY (
        select ae.aid
        from RangEquipe re, AthletesEquipe ae
        where re.eqid = ae.eqid
    )
