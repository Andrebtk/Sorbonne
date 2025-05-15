function fournir_page ($r)
<?php
{
    list($status, $entetes, $page) = $r;
    header("HTTP/1.1 $status");
    foreach ($entetes as $nom => $valeurs)
        foreach($valeurs as $valeur)
            header("$nom: $valeur");
    echo $page;
}
?>