<?php
    include "../TME2/re_url.php";
    include "http_args.php";
    include "../TD4/lire_entetes.php";
    include "re_http_status.php";

    function requeter_en_http ($url, $req='GET', $version='1.1', $entetes=array())
    {
        if (!preg_match(RE_URL, $url, $r) OR (!$r[1]))
            return array(400, array(), "Mauvaise URL: $url");
        list($tout, $schema, $serveur, $port, $ressource,) = $r;
        if (!$port) $port = 80;
        $sock = fsockopen($serveur,$port);
        if (!$sock)
            return array(500 , array(), "$serveur:$port injoignable");
        else {
            $args = http_args($serveur, $entetes, $version);
            if (!fputs($sock, "$req $url $args"))
                return array(500 , array(), "$serveur:$port injoignable");
            $rep = fgets($sock);
            $entetes = (preg_match(RE_HTTP_STATUS, $rep, $m) AND $m[1] >= 1)
                    ? lire_entetes($sock) : array();
            $page='';
            while ( !feof($sock) ) $page .= fgets($sock);
            return array(isset($m) ? $m[2] : 200, $entetes, $page);
        }
    }

?>