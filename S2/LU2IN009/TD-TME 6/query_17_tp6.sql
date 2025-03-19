select s.nomSp
from sport s
where NOT EXISTS (
    select *
    from epreuve e
    where e.sid=s.sid AND datediff(day, e.datedebut, e.datefin)>0
)