select s.Nomsp
from sport s
where NOT EXISTS (
    select *
    from Epreuve e
    where e.sid = s.sid AND e.categorie='Mixte'
)