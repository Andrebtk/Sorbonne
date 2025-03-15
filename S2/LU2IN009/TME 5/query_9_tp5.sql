select DISTINCT a.nomAth, a.prenomAth
from Athlete a, RangIndividuel ri
where ri.aid = a.aid AND ri.rang is NULL 
    AND EXISTS (
        select *
        from RangIndividuel ri1
        where ri1.rang in (1,2,3) AND ri1.aid=a.aid 
)