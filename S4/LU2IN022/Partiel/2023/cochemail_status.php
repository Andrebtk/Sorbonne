<?php 

    include 'cochemail_smtp.php';

    function cochemail_status($dico, $moi, $blabla, $dest) {

        header("Content-Type: text/html charset=utf-8");
        $t = cochemail_smtp($dico, $moi, $blabla, $dest);

        if($t == 0) {
            echo date("Y/m/d h:i:m\n") . $dico['ok'] . join(' ', $dest);
        } else {
            header("HTTP/1.1 " . $t);
        }
        echo date("Y/m/d h:i:m\n") . $dico['ko'] . $balbla;

    }

?>