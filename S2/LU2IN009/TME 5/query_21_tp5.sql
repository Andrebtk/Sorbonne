select DISTINCT a.nomAth, a.prenomAth, s.nomSP, e.nomEP, ri1.rang
from Athlete a, RangIndividuel ri1, sport s, epreuve e
where e.sid=s.sid AND a.aid = ri1.aid AND ri1.epid=e.epid AND ri1.rang is not NULL AND NOT EXISTS (
    select *
    from Athlete b, RangIndividuel ri2, epreuve e2
    where e2.sid = s.sid AND b.aid <> a.aid AND ri2.epid=e.epid AND ri2.aid = b.aid 
        AND ri2.rang is not NULL AND ri2.rang >ri1.rang
)