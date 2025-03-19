select DISTINCT sport,epreuve,categorie
from rangepreuve
where datediff(day,datedebut, datefin)+1 between 2 AND 4