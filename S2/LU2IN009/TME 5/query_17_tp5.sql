select *
from equipe e
where NOT EXISTS (
    select *
    from athlete a, AthletesEquipe ae
    where ae.aid = a.aid AND ae.eqid = e.eqid
)