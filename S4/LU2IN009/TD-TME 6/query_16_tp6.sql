select DISTINCT s1.NSP
from Sponsorise s1,Sponsorise s2 
where s1.NSP=s2.NSP AND EXISTS (
    select *
    from Joueur j1, Joueur j2, match m1, match m2, Distance d
    where j1.Njo <> j2.Njo AND m1.eq1=j1.eq AND m2.eq1 = j2.eq AND m1.st <> m2.st AND d.st1 = m1.st 
        AND d.st2=m2.st AND d.NbKm<50 AND s1.Njo = j1.Njo AND s2.Njo=j2.Njo AND DAY_OF_WEEK(m1.dateM)=DAY_OF_WEEK(m2.dateM)
)