<?php
    include "rdv.re.php";

    function rdv_match($ti, $tm) {
        $rep = array();

        foreach($ti as $i) {
            if (isset($tm[$i]) AND (preg_match(RE_MAIL_DOMAIN, $tm[$i], $m)) ) {
                $rep[] = $m;
            } else {
                return array();
            }
        }

        return $m;
    }

?>