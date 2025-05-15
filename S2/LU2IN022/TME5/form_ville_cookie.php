<?php

include "trouver_sous_index.php";
include "destination.php";
include "../TD3/html_form.php";
include "soumission_multiple.php";
include "../TME2/debut_html.php";
include "../TD2/tableau_en_table.php";

$item = isset($_POST['item']) ? $_POST['item'] : 1;
$pays = isset($_POST['pays']) ? $_POST['pays'] : '';
$visite =  isset($_COOKIE['visite']) ? $_COOKIE['visite'] : 1;

$villes = trouver_sous_index($destinations, $pays);

if (!$villes) {
    header("HTTP/1.1 303");
    header("Location: form_pays.php");
} else {
    $titre = "Bon voyage";
    if (is_numeric($item)) {
        $pays = htmlspecialchars($pays, ENT_QUOTES);
        $hidden = "<input type='hidden' name='pays' value='$pays' />";
        $body = html_form(soumission_multiple($villes, $item) . $hidden, 'post');
        $duree = time()+(7*24*60*60);
    } else {
        if (isset($villes[$item]))
            $body = "Bon séjour à $item pour " . ($villes[$item]*$visite) . "€.";
        else $body = "Ville inconnue";
        $duree = 0;
    }
    
    setcookie('visite', $visite+1, array('samesite' => 'Strict', 'expires' => $duree));

    echo debut_html($titre),
        "<body><div><h1>$titre$visite</h1>\n$body</div></body></html>\n";
}
?>