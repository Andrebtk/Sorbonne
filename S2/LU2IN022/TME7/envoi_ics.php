<?php 
    

    function envoie_ics($tab, $str) {
        if(empty($tab)) {
            header('Content-Type: "text/plain; charset=utf-8"');
            echo $str;
        }
        else {
            header('Content-Type: "text/calendar; charset=utf-8"');
            header("Content-Transfer-Encoding: 8bit");
            header('Content-Disposition: inline; filename="' . $str . '.ics"');
            foreach($tab as $l=>$d){
                echo $d;
            }
        }
        
    }

    //envoie_ics(fusionne_ics("cal1.ics", "cal2.ics"), "res");
?>