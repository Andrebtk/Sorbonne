select nom, prenom, pays
from Athlete
where pays in ('Danemark', 'Finlande', 'Norvège', 'Suède', 'Islande')
ORDER BY nom, prenom