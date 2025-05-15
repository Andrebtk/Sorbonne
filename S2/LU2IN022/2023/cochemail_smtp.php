<?php
    include "cochemail_requeter.php";

    function cochemail_smtp($dico, $moi, $blabla, $dest) {
        $sock = @fsockopen('127.0.0.1', 790, $errno, $errstr);
        
        if ($sock == false){
            return 500;
        }

        if(($a1 = cochemail_requeter($sock, "HELO localhost")) !=0){
            cochemail_requeter($sock, "QUIT");
            @fclose($sock);
            return $a1;
        }
        
        if(($a2 = cochemail_requeter($sock, "MAIL FROM: $moi")) != 0){
            cochemail_requeter($sock, "QUIT");
            @fclose($sock);
            return $a2;
        }

        foreach ($dest as $v) {
            if (($t = cochemail_requeter($sock, "RCPT TO: $v"))!=0){
                cochemail_requeter($sock, "QUIT");
                @fclose($sock);
                return $t;
            }
        }

        if (cochemail_requeter($sock, "DATA") == 351){
            cochemail_requeter($sock, $blabla . "\n.\n");
            return 0;
        }
       
        cochemail_requeter($sock, "QUIT");
        @fclose($sock);
    }
    cochemail_smtp("","","","");

?>