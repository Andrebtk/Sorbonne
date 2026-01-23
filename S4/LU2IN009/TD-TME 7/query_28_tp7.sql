select round(avg(c),3)
from (select count(*) as c
        from athlete a
        group by a.codepays)