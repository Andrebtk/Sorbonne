select DISTINCT m.datem
from match m
where EXISTS (
    select *
    from Sponsorise s1, Sponsorise s2, Joueur j1, Joueur j2
    where s1.NSP <> s2.NSP AND s1.Njo = j1.Njo AND s2.Njo = j2.Njo AND j1.eq = m.eq1 AND j2.eq = m.eq2
)