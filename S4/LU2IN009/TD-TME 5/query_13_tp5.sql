select DISTINCT s.nomSP
from epreuve e, sport s
where e.sid = s.sid AND EXISTS (
    select *
    from athlete a, RangIndividuel ri
    where a.nomATH='LESSER' AND a.prenomATH='Erik' AND ri.epid=e.epid AND ri.aid = a.aid
)