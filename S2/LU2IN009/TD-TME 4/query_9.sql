select nomath, prenomath, rang
from rangepreuve
where sport='Ski de fond' AND epreuve='10km' AND rang is not NULL
ORDER BY rang