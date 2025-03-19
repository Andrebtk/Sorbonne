select a.nomAth, a.prenomAth
from Athlete a
where EXISTS (
    select *
    from RangIndividuel ri1, RangIndividuel ri2, epreuve e1, epreuve e2
    where ri1.aid = a.aid AND ri2.aid = a.aid AND ri1.epid <> ri2.epid AND e1.sid <> e2.sid 
        AND e1.epid = ri1.epid AND e2.epid = ri2.epid 
)