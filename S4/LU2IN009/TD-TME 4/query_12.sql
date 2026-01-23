select DISTINCT sport,epreuve,categorie
from RangEpreuve
where DAY_OF_WEEK(datefin) in (1,7)