select a.codepays, count(*)
from athlete a
group by a.codepays
order by count(*)