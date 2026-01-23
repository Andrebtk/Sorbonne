select e.eqid
from Equipe e
where NOT EXISTS (
    select *
    from AthletesEquipe ae, RangIndividuel ri
    where ae.eqid=e.eqid AND ae.aid=ri.aid AND ri.rang in (1,2,3)
)