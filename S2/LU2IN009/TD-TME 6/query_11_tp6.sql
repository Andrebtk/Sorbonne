select s.nomSp, e.nomEp, e.categorie, datediff(day, e.datedebut, e.datefin)
from sport s, epreuve e
where s.sid = e.sid AND 
    datediff(day, e.datedebut, e.datefin) >= ALL (
            select datediff(day, e1.datedebut, e1.datefin)
            from epreuve e1
        )