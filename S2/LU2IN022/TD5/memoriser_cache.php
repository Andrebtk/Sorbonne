<?php
function memoriser_cache ($dir, $nom, $entetes, $page)
{
    $f = "$dir/$nom" . ".http";
    $t = file_put_contents($f, serialize($entetes));
    if ($t) {
        $f = "$dir/$nom" . "." . typer_cache($entetes);
        $t = file_put_contents($f, $page);
    }
    return $t;
}
?>