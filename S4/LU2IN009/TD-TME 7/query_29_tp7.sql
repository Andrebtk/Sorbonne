select eqid, count(*)
from AthletesEquipe
group by eqid
order by count(*) DESC