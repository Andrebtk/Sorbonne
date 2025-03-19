select a.nomAth, a.prenomAth
from Athlete a
where a.aid NOT IN (
    select ri.aid
    from rangIndividuel ri
    where ri.rang in (1,2,3) AND ri.aid=a.aid
) AND a.aid NOT IN (
    select ae.aid
    from RangEquipe re, AthletesEquipe ae
    where ae.eqid = re.eqid AND re.rang in (1,2,3)
)