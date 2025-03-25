select round(avg(datediff(year, a.dateNaissance, date '2014-02-06')),1)
from Athlete a
where a.codepays='FRA'