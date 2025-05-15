<?php 
    /*
    function trouver_cache($folder, $nom) {
        if(is_readable("$folder/$nom.http")) {
            $header = unserialize(file_get_contents("$folder/$nom.http"));
            if($header != false) {
                if(!ignorer_cache($header)) {
                    $type = typer_cache ($headers);
                    if(is_readable("$folder/$nom.$type")) {
                        $body = file_get_contents("$folder/$nom.$type");
                        return array('200',$header, $body);
                    }
                }
            }
        }

        return array();
    }
    */
    function trouver_cache ($dir, $nom){
        $f = "$dir/$nom" . '.http';
        if (!is_readable($f))
            return array();
        $h = unserialize(file_get_contents($f));
        if (!$h OR ignorer_cache($h))
            return array();
        $f = "$dir/$nom" . '.' . typer_cache($h);
        if (!is_readable($f))
            return array();
        return array(200, $h, file_get_contents($f));
    }
?>