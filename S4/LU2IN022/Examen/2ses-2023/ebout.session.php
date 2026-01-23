<?php 

    function ebout_session($articles) {
        if(!isset($_SESSION['panier'])) return "commande vide\n";
        $prix = 0;
        $res = "";
        foreach($_SESSION['panier'] as $id=>$quant){
            $res .= $quand . $id;
            $prix += $quand * $articles[$id]['prix'];
        }

        return $res . "Total de la commande :" . $prix;
        
    }


?>