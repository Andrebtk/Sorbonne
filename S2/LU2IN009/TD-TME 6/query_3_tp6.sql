select p.nomp
from Pays p, Athlete a
where a.codepays =p.codepays AND NOT EXISTS (
        select *
        from Athlete b
        where b.aid <> a.aid AND b.codepays = p.codepays
    )