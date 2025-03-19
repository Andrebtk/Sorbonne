select a.nomAth, a.prenomAth
from Athlete a
where EXISTS (
    select *
    from RangIndividuel ri
    where ri.aid = a.aid AND ri.rang=1
)
AND NOT EXISTS (
    select *
    from RangIndividuel ri
    where ri.aid=a.aid AND ri.rang in (2,3)
)