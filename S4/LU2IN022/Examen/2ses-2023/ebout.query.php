<?php 

    function ebout_query($tab, $enPost) {
        $res = "";
        foreach($tab as $id=>$val){

            $id_article = "";
            $d = "<div class='article' id='$id_article'>\n"
                . "<img url='". $val['media'] ."'\n"
                . "<h2>". $val['description'] ."</h2>\n"
                . "<p class='prix' onmouseover ='ebout_position(this)'>". $val['prix'] . "€</p>"
                
                . "<span style='display:none'>". /*(isset($_SESSION['panier'][$id_article])) ? $_SESSION['panier'][$id_article]: 0 */"</span>";


            $res .= $d . "\n</div>\n";
        }
        return $res;
    }

    /*echo ebout_query(array(
     'X21' =>
       array (
         'prix' => '14.20',
         'categorie' => 'C1' ,
         'media' => 'bklomUCxL.jpg' ,
         'description' => 'Smart 360 Flex Jean Cut Slim',
         'genre' => array (
                       0 => 'Homme'
         ),
        'mot-clef' => array (
                        0 => 'Accessoire' ,
                        1 => 'Vêtement'
                    )
    )), false);*/

?>