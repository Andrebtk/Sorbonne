<?php 

    include 'requeter_en_pop.php';
    include 'lire_entetes.php';
    include 'lire_message_pop.php';

    /*
    function choisir_message_pop($sock, $entete) {
        $nbMess = requeter_en_pop ($sock, "STAT");
        $res = array();
        if ($nbMess != false) {
            $n = intval($nbMess);

            for ($i=0; $i<$n; $i++) {
                requeter_en_pop ($sock, "RETR $i");
                $body = lire_message_pop($sock);
                $ent = lire_entetes($sock);

                $valid = true;
                foreach ($entete as $k=>$v) {
                    if(!isset($ent[$k]) OR $ent[$k] != $v){
                        $valide = false;
                        break;
                    }
                }

                if ($valid) {
                    $res[] = array($i, $ent, $body);
                }
            }
        }

    }
    */

    function choisir_message_pop ($sock, $criteres) {
        // intval renvoie le PREMIER entier dans une chaine,
        // et 0 si son argument est égal à false, c'est ce qu'il faut.
        $n = intval(requeter_en_pop($sock, "STAT"));
        $res = array();
        for (;$n;--$n) {
            requeter_en_pop($sock,"RETR $n");
            $entetes = lire_entetes($sock);
            $message = lire_message_pop($sock);
            $ok = true;
            foreach ($criteres as $nom => $val) {
                if (!isset($entetes[$nom]) OR ($entetes[$nom][0] != $val)) {
                    $ok = false;
                    break;
                }
            }
            if ($ok) {
                $res[] = array($n, $entetes, $message);
            }
        }
        return $res;
    }

?>