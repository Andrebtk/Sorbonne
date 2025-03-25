select count(c)
from (select count(*) as c
        from RangIndividuel ri
        group by ri.epid
        having count(*) > 100)