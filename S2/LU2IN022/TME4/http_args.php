<?php
    /// On profite de la conversion implicite en nombre
    /// d'une chaîne utilisée avec un opérateur arithmétique.
    function http_args ($serveur='', $entetes=array(), $version='') {
        if ($version < 1)
            return "\r\n";
        if ($version > 1) $entetes[]= "Host: $serveur";
        return "HTTP/$version\r\n" . join("\r\n", $entetes) . "\r\n\r\n";
    }
    /*/
    echo http_args('localhost', array('Content-Type: image/png'), 1.1);
    //*/
?>