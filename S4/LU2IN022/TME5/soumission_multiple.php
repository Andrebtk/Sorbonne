<?php 
    /// Construit 3 boutons de soumissions permettant de naviguer et choisir
    /// dans un catalogue decrit par le tableau $catalogue de forme:
    /// array(article1 => prix1, article2 => prix2, ....)
    /// $n est le numero de page en cours de consultation

    function soumission_multiple ($villes, $n)
    {
        if (($n <= 0) OR ($n > count($villes))) $n = 1;
        if ($n > 1)
            $p = "<input type='submit' name='item' value='" . ($n-1) . "' />\n";
        else $p = '';
        if ($n < count($villes))
            $s = "<input type='submit' name='item' value='" . ($n+1) . "' />\n";
        else $s = '';
        $destination = cherche_index_n($villes, $n);
        $prix = $destination ? $villes[$destination] : "?";
        $v = htmlspecialchars($destination, ENT_QUOTES);
        $choix = "<input type='submit' name='item' value='$v' />$prix €";
        return "<ul><li>$p</li>\n<li>$choix</li>\n<li>$s</li></ul>";
        /// ou bien: tableau_en_liste(array($p, $choix, $s)
    }
?>