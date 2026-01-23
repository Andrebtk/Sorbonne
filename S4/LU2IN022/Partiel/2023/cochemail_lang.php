<?php

    define('min','/([a-z]+)/');

    function cochemail_lang($libelles, $str) {
        if(preg_match(min, $str, $m) AND isset($libelles[$m[1]])) {
            return $libelles[$m[1]];
        }
        return $libelles['fr'];
    }

?>
