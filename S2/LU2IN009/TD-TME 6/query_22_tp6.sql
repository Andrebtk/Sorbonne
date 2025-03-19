select a.nomAth, a.prenomAth, p.nomp
from athlete a, pays p
where a.codePays = p.codepays AND a.dateNaissance is not NULL 
    AND NOT EXISTS (
    select *
    from Athlete b
    where a.aid <> b.aid AND a.codePays = b.codePays AND b.dateNaissance is not NULL
        AND datediff(day, a.dateNaissance, b.dateNaissance)>0
)