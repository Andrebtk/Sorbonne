select *
from Pays p
where p.codepays = ANY (
        select a.codepays
        from athlete a
    ) AND NOT EXISTS (
        select *
        from Athlete a, RangIndividuel ri
        where a.codepays = p.codepays AND a.aid=ri.aid AND ri.rang IS NULL
    )