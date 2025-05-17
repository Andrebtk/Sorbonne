<?php 

    function authentifie($num_etu, $pass) {
        $f = file_get_contents("mots_de_passe.txt");

        
        if(preg_match('/'.$num_etu.' : ([^;]+)/',$f,$m)) {
            if($m[1] == $pass) return true;
        }
        return false;
    }

    //echo "test:" . (authentifie('21210001','axSd2$asdDF5') ? 'true' : 'false') . "\n";

?>