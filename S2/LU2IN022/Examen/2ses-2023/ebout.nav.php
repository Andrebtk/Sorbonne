<?php 

    function ebout_nav($categories) {
        $res ="<ul class='nav'>\n";

        foreach($categories as $c=>$val) {
            $res.= "<li><button id='$c' onclick='ebout_ajax_post($c)'>$val</button></li>\n";
        }

        return $res . "</ul>\n";
    }
    echo ebout_nav(array('C1' => 'Noeuds' ,'C2' => 'Chemises'))
?>