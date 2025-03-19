select *
from pays p
where EXISTS (
    select *
    from Athlete a
    where a.datenaissance is not null AND a.codepays = p.codepays
        AND (datediff(day, a.datenaissance, DATE '2016-02-24')<(18*365)
        OR datediff(day, a.datenaissance,DATE '2016-02-24')>(40*365))
)