select s.nomSp
from Sport s
where s.sid NOT IN (
    select e.sid
    from Epreuve e
    where lower(e.categorie)='mixte'
)