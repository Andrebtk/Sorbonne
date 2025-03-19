select m.st
from match m
where EXISTS (
    select *
    from Joueur j
    where j.njo='Manon Messi' AND m.eq1=j.eq
)