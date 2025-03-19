select a.nomAth, a.prenomAth
from athlete a
where EXISTS (
    select *
    from RangIndividuel ri
    where ri.aid = a.aid AND ri.rang in (1,2,3)
)