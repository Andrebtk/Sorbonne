select eqid
from athletesEquipe
group by eqid
having count(*) = 10