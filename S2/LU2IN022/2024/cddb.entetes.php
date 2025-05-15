<?php 
    include "cddb.socket.php";

    function cddb_entetes($suite, $lang) {
        list($codeReponse, $entetes, $resultat) = cddb_socket($suite,$lang);
        header("HTTP/1.1" . $codeReponse);
        header("Content-Type: text/html charset='" . $entetes['Content-Type'] . "'");
        

        if($codeReponse == 200) {
            $titre = array_shift($resultat);
            $body = '<ol>';
            foreach($resultat as $v) {
                $body .= '<li>'. $v .'</li>';
            }
            $body .= '</ol>';
        } else if ($codeReponse == 207) {
            $titre = "Disponible dans d'autres langues";

            $body = '<ol>';

            foreach($entetes['Content-Language'] as $v) {
                $body .= "<li><a href='cddb.get.php?suite=$suite&lang=$v'>$v</a></li>";
            }
            $body .= '</ol>';
        } else if ($codeReponse == 202) {
            $titre = "Ambiguites";
            $body = '<select name="suite">';
            $i=1;
            foreach($entetes['Article-Names'] as $v) {
                $body .= "<option value='" . trim($resultat[0])." -$i'>". htmlspecialchars($v) ."</option>";
                $i++;
            }
            $body .= "</select>";
            $body = html_form($body. "<input type='submit'>", );
        }
        
        
        echo cddb_html($titre, $body, $entetes['Content-Type'], $entetes['Content-Language'][0]);
    }
    


?>