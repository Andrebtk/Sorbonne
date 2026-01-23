<?php
function actualiser_cache ($md5, $visites, $dir, $max)
{
    $tab = is_readable($visites)
         ? unserialize(file_get_contents($visites))
         : array();
    $tab[$md5] = time();
    if (count($tab) > $max) {
        asort($tab);
        $md5 = key($tab);
        $h = "$dir/$md5" . '.http';
        $t = "$dir/$md5" . '.' . typer_cache(unserialize(file_get_contents($h)));
        unlink($h);
        unlink($t);
        array_shift($tab);
    }
    file_put_contents($visites, serialize($tab));
}
?>