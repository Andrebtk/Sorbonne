select s.nomSP, e.nomEp, e.categorie
from Epreuve e, RangEquipe re, sport s
where s.sid = e.sid AND e.epid = re.epid
