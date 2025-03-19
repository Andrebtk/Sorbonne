select *
from pays p
where p.codepays = ANY (
    select a.codepays
    from Athlete a
) AND NOT EXISTS (
    select *
    from RangIndividuel ri, Athlete a
    where ri.rang in (1,2,3) AND a.codepays=p.codepays AND a.aid=ri.aid
) AND NOT EXISTS (
    select *
    from RangEquipe re, Equipe e
    where e.codepays = p.codepays AND re.eqid = e.eqid AND re.rang in (1,2,3)
    
)