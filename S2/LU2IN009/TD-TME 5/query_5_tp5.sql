select ep.nomep
from Pays p, Equipe e, RangEquipe re, Sport s, epreuve ep
where e.codepays=p.codepays AND re.eqid =e.eqid AND re.rang=1 
    AND ep.epid=re.epid AND ep.sid=s.sid AND lower(s.Nomsp)='biathlon' 
    AND lower(ep.categorie)='femmes' AND lower(ep.nomep)='relais 4x6km'