select * 
from pays p
where p.codepays = ANY (
        select a.codepays
        from athlete a
    ) AND NOT EXISTS (
        select *
        from athlete a1, RangIndividuel ri
        where a1.codepays=p.codepays AND ri.aid =a1.aid AND ri.rang is NULL
    ) AND NOT EXISTS (
        select *
        from equipe e, RangEquipe re
        where e.codepays=p.codepays AND re.eqid=e.eqid AND re.rang is NULL
    )