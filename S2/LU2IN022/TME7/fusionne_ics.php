<?php 

    function fusionne_ics($tab1, $tab2) {
        $ics1 = (is_array($tab1)) ? $tab1 : file($tab1); 
        $ics2 = (is_array($tab2)) ? $tab2 : file($tab2); 
        array_pop($ics1);
        
        array_shift($ics2);
        while(!preg_match("/BEGIN/", $ics2[0])) {
            array_shift($ics2);
        }
        
        return array_merge($ics1, $ics2);
    }


?>