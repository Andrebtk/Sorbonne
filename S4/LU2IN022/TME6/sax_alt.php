<?php 
    include 'sax_echo.php';

    $nunix =  "][(){}<>|&;'\""; 
    define('RE_CHEMIN',
       "@^([^$nunix]*?)([^$nunix/]*?)(?:[.]([\d\w]+))?$@");

    class sax_alt extends sax_echo {
        
        
        function tableau_en_attributs($tab, $nom) {
            if(($nom == 'img') AND (!isset($tab['alt']))) {
                preg_match(RE_CHEMIN, $tab['src'], $m);
                $tab['alt'] = $m[2];
            }

            return parent::tableau_en_attributs ($tab, $nom);
        }



    } 
    //phraser('test.html', new sax_alt);
?>  