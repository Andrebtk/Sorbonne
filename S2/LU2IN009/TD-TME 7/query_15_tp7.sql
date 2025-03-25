select dateObs, count(*), max(valobs)
from observation 
group by dateobs
having max(valobs) > 8000