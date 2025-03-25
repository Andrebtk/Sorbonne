select idc, max(rayon)
from astre
group by idc
Order By max(rayon)