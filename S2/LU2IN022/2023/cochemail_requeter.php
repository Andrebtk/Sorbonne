<?php 

    function cochemail_requeter($sock, $req) {
        if (!fputs($sock, trim($req) . "\r\n")) return 500;
        $reponse = fgets($sock);
        return preg_match("/^(\d\d\d)/", $reponse, $m) 
            ? ($m[1] > 350) ? $m[1]: 0 
            : 500;
    }

?>