select a.nomAth, a.prenomAth 
from athlete a
where EXISTS (
    select *
    from rangIndividuel ri1, rangIndividuel ri2
    where ri1.aid = a.aid AND ri2.aid = a.aid AND ri1.epid <> ri2.epid
)