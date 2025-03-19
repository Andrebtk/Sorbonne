select eq1
from match m
where EXISTS (
    select *
    from equipe e
    where lower(e.neq)='piepla' AND m.st=e.stp
)