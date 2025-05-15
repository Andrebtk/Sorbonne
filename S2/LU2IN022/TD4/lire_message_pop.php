<?php

    function lire_message_pop($sock) {
        $rep = "";
        while((trim($data = fgets($sock))) != ".") {
            $res .= $data;
        }
        return $data;

    }

?>