select * 
from pays p
where p.codepays = ANY (
        select a.codepays
        from athlete a
    )