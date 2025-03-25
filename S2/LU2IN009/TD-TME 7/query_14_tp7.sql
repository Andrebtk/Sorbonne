select idc
from Astre
group by idc
having count(*) >= 2