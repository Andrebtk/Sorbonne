<?php
    include '../TD2/tableau_en_liste.php';
    include '../TD3/tableau_pour_cocher.php';
    function cochemail_form($libelles, $dest, $choisis=array(), $moi='', $blabla='')
    {
        $dest = tableau_en_liste(tableau_pour_cocher($dest, 'dest', $choisis));
        $moi = "<div><label for='moi'>"
            . $libelles['moi']
            . "</label>\n<input id='moi' name='moi' value='"
            . htmlspecialchars($moi, ENT_QUOTES)
            . "'/></div>\n";
        $blabla = "<label for='blabla'>"
                . $libelles['blabla']
                . "</label>\n<textarea id='blabla' name='blabla'>"
                . htmlspecialchars($blabla)
                . "</textarea>\n";
        return "<form action='' method='post'><fieldset>\n"
            . $moi
            . $dest
            . $blabla
            . "<input type='submit' /></fieldset></form>";
    }
    /*// Test
    echo cochemail_form(array('1@1', '2@2', '3@3'));
    //*/

?>