select a.codepays, count(*), count(distinct a.aid)
from athlete a, RangIndividuel ri
where a.aid = ri.aid AND ri.rang in (1,2,3)
group by a.codepays
order by count(*) DESC