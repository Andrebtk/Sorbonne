<?php

    include "../TD4/ouvrir_session_pop.php";
    include "../TD4/fermer_session_pop.php";
    include "../TD4/requeter_en_pop.php";
    include "../TD4/lire_entetes.php";

    function webmail_pop($username, $password, $port) {
        $sock = ouvrir_session_pop('127.0.0.1',$username,$password,$port);
        if(is_string($sock)) {
            $m = "connexion échoue" . $sock;
        } else {
            $n = intval(requeter_en_pop($sock, "STAT"));
            $res = array();

            for (;$n;--$n) {
                requeter_en_pop($sock,"RETR $n");
                $entetes = lire_entetes($sock);
                if (isset($entetes['From'])) {
                    
                    $value = $entetes['From'][0];
                    if (isset($res[$value])) {
                        $res[$value]++;
                    }else {
                        $res[$value] = 1;
                    }
                }
            }
            
            ksort($res);
            
           
            $m ='';
            foreach($res as $from=>$num) {
                $m .=  "$from -> $num\n";
            }
            echo $m;
            fermer_session_pop($sock);
        }
        header('Content-Type: text/plain;charset=utf-8');
        echo $m;
    }
//port ->  2110
?>
