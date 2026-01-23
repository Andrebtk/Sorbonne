select a.nomAth, a.prenomAth
from Athlete a
where NOT EXISTS (
    select *
    from RangIndividuel ri1
    where ri1.aid=a.aid AND NOT EXISTS (
        select *
        from RangIndividuel ri2
        where ri2.rang in (1,2,3) AND ri2.aid = a.aid AND ri1.epid=ri2.epid
    )
)
-- Pas le bon nombre de ligne