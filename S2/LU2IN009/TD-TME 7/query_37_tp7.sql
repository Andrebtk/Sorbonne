select p.nomp 
from RangIndividuel ri, athlete a, pays p
where a.aid = ri.aid AND ri.rang in (1,2,3) AND p.codepays = a.codepays
group by a.codepays
having count(*)>=20