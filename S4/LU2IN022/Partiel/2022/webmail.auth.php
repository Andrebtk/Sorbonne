<?php 
    define('TES','/^(\w+);(\w*);(.*)/');

    function webmail_auth($nom, $mdp) {
        $mdp = md5('$mdp');
        $f = file("webmail.users.txt");
        foreach($f as $lineN => $line) {
            if(preg_match(TES, $line, $m)) {
                if( ($m[1] == $nom) /*AND ($mdp == $m[2])*/ ) {
                    return $m[3];
                }
            }
        }

        return false;
    }

?>