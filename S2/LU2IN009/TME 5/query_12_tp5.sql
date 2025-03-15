select DISTINCT a.nomAth, a.prenomAth
from Athlete a, RangIndividuel ri1, RangIndividuel ri2
where ri1.epid <> ri2.epid AND a.aid = ri1.aid AND a.aid = ri2.aid 
    AND NOT EXISTS (
        select *
        from RangIndividuel ri3
        where ri3.epid <> ri1.epid AND ri3.epid <> ri2.epid AND ri3.aid = a.aid
    )