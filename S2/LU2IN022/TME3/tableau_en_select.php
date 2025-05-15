
<?php 
/*
    include "destination.php";

    function tableau_en_select($tab, $nom, $str="") {
        $res = "<select >";
        foreach ($tab as $k=>$pays) {
            $res .= "<optgroup label='$k'>";
            foreach($pays as $k2=>$villes) {
                if ($str == $k2) {
                    $res .= "<option selected value='$k2'>$k2</option>";
                } else {
                    $res .= "<option value='$k2'>$k2</option>";
                }
               
            }
            $res .= "</optgroup>";
        }
        return $res . "</select>";
    }

    echo tableau_en_select($destinations, "", "Japon");
*/
?>

<?php
/// Cette fonction a été concue en ecrivant ses lignes dans cet ordre:
/// 1 2 3 4 6 8 9 10 7 11 12 5 13 14 15 16 17 18 19 20 21 22
function tableau_en_select ($options, $nom, $choix='')
{
    $sel = "\n\t<option></option>";
    foreach ($options as $titre => $listes) {
        $groupes = '';
        foreach($listes as $indice => $valeur) {
            $c = ($indice == $choix) ? " selected='selected'" : "";
            $desc = is_string($valeur) ? $valeur : $indice;
            $v = htmlspecialchars($indice, ENT_QUOTES);
            $groupes .= "\n\t<option value='$v'$c>$desc</option>";
        }
        if (count($options) == 1) {
            $sel .= $groupes; /// bonus: pas d'optgroup si un seul groupe
        } else {
            $t = htmlspecialchars($titre, ENT_QUOTES);
            $sel .= "\n\t<optgroup label='$t'>$groupes</optgroup>";
        }
    }
    return "<label for='$nom'>$nom</label>\n"
        .  "<select id='$nom' name='$nom'>$sel</select>\n";
}
/*// Test
var_dump(tableau_en_select(array(array('un', 'deux')),'num'));
var_dump(tableau_en_select(array('g1' => array('A', 'B')),'num'));
var_dump(tableau_en_select(array('g2' => array('C', 'D')),'num', 1));
//*/
?>