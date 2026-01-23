<?php
    /// 1. 
    function tableau_en_table ($tab, $nom)
    {
        if (!$tab) return '';
        $chaine = "";
        foreach($tab as $k => $v)
            $chaine .= "<tr>\n<td>$k</td>\n<td>$v</td>\n</tr>\n";
        $th = "<tr>\n<th>Nom</th>\n<th>Valeur</th>\n</tr>\n";
        return "<table>\n<caption>$nom</caption>\n$th$chaine$th</table>\n";
    }

    /// 2.
    function cherche_index_n ($tab, $n)
    {
        foreach($tab as $k => $v) {
            /* OU
                $n--;
                if($n==0) return $k;
            */
            if (!--$n) return $k;
        }
        return false;
    }

    /*// Test
    $Scores = array("candidatA"=>130,"candidatB"=>300,"candidatC"=>30);
    echo tableau_en_table($Scores, 'scores'), "\n";
    echo cherche_index_n($Scores, 2), "\n";
    //*/
?>
