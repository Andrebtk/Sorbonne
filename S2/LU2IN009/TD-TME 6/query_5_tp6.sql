Select *
FROM pays p 
where p.codepays NOT IN (
        select a.codepays
        from Athlete a, RangIndividuel ri
        where ri.aid = a.aid AND ri.rang is NULL)
