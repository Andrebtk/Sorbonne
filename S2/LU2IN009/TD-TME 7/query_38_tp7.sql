select sid
from epreuve
group by sid
having count(distinct categorie) = (select count(distinct categorie)
                                        from epreuve )