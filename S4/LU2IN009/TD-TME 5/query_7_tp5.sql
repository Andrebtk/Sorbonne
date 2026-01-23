select DISTINCT a.nomATH
from athlete a
where EXISTS (
    select *
    from athlete b
    where a.aid<>b.aid and a.nomATH=b.nomATH
)