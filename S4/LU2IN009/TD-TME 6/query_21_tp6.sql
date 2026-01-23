select a1.dateNaissance, a1.codePays
from Athlete a1
where a1.dateNaissance is not NULL AND NOT EXISTS (
    select *
    from Athlete a2
    where datediff(day, a1.dateNaissance, a2.dateNaissance)>0 AND a2.aid <> a1.aid
)