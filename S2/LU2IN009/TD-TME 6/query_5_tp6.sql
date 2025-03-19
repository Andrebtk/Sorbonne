Select *
FROM pays p 
where p.codepays NOT IN (
        select a.codepays
        from Athlete a, RangIndividuel ri
        where ri.aid = a.aid AND a.codepays=p.codepays AND ri.rang is NULL)