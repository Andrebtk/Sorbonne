select e.nomep, e.categorie, s.nomsp
from epreuve e, Sport s
where s.sid = e.sid
ORDER BY e.nomep DESC