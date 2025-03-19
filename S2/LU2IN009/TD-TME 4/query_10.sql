select DISTINCT sport,epreuve,categorie
from rangepreuve
where datediff(day,DATE '2014-02-21', datedebut)>0