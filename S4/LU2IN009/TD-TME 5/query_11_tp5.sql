select p.nomP
from pays p, equipe e1
where e1.codepays = p.codepays 
    AND NOT EXISTS (
        select *
        from equipe e2
        where e2.codepays = p.codepays AND e1.eqid <> e2.eqid 
)