(select sport, epreuve, categorie,
from RangEpreuve)

EXCEPT

(select sport, epreuve, categorie,
from RangEpreuve where rang = 2)