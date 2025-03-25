select count(distinct a.aid)/count(distinct p.codepays)
from pays p, athlete a
where a.codepays = p.codepays