select idc, count(*)
from Astre
group by idc
Order by count(*) DESC