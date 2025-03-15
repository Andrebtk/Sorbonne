select DISTINCT e1.datedebut, e2.datefin
from epreuve e1, epreuve e2
where NOT EXISTS (
    select *
    from epreuve e3
    where datediff(day, e1.datedebut, e3.datedebut)<0
)
AND NOT EXISTS (
    select *
    from epreuve e4
    where datediff(day, e2.datefin, e4.datefin)>0
)