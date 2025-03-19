select s.nomSp, e.nomEp, e.categorie, datediff(day, e.datedebut, e.datefin)
from sport s, epreuve e
where s.sid = e.sid AND NOT EXISTS (
        select *
        from sport s1, Epreuve e1
        where s1.sid = e1.sid AND e1.epid <> e.epid 
            AND datediff(day, e1.datedebut, e1.datefin) > datediff(day, e.datedebut, e.datefin)
)