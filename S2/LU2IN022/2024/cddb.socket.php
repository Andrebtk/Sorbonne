<?php 

    define('RE_ENTETE', "/^([A-Z][A-Za-z]*(?:-[A-Z][A-Za-z]+)?):\s+(.*?)\s*$/");

    function cddb_socket($suite, $lang, $port=8080, $serveur="127.0.0.1") {
        $sock = fsockopen($serveur,$port, $erreurCode, $erreurMessage);

        $entetes = array();
        $resultat = array();
        
        if(!$sock) {
            $resultat[] = $erreurMessage;
            return array(500, $entetes, $resultat);
        }
        fgets($sock); //message de bienvenue du serveur
        fputs($sock, "DISC $suite\nAccept-Language=$lang\n\n");
        $codeReponse = fgets($sock);

        while (trim($ligne = fgets($sock))) {

            if (preg_match(RE_ENTETE, $ligne, $r)){
                $cle = $r[1];
                if (!isset($entetes[$cle])){
                    $entetes[$cle] = array($r[2]);
                } else {
                    $entetes[$cle][] = $r[2];
                }              
            } else {
                /// Autre ligne : ajout a la derniere cle trouvee
                $entetes[$cle][count($entetes[$cle])-1] .= $ligne;
            }
        }

        while((trim($data = fgets($sock)))) {
            $resultat[] = $data;
        }

        fclose($sock);

        return array($codeReponse, $entetes, $resultat);
    }

    //var_dump(cddb_socket("30 300 310 320 330", "fr"));
?>
