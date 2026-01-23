select s.nomsp, count(*)
from epreuve e, sport s
where s.sid = e.sid
group by e.sid
order by count(*) DESC