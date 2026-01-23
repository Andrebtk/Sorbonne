select eqid
from athletesEquipe
group by eqid
having count(*) = (select max(c)
                    from (select count(*) as c
                        from athletesEquipe
                        group by eqid))