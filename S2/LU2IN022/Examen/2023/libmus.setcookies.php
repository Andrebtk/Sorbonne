<?php 

    function libmus_setcookies($search, $type) {
        $arg = array('samesite' => 'Strict', 'expires'=>time()+3600);
        setcookie("recherche", $search, $arg);
        setcookie("type", $type, $arg);
        setcookie("date_heure",date("d.m.y H:i:s"),$arg);
    }

?>