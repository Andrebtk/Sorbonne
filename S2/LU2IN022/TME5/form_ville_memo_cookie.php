<?php

include "trouver_sous_index.php";
include "destination.php";
include "../TD3/html_form.php";
include "soumission_multiple.php";
include "../TME2/debut_html.php";
include "../TD2/tableau_en_table.php";
include "pister_visiteur.php";

$item = isset($_POST['item']) ? $_POST['item'] : 1;
$pays = isset($_POST['pays']) ? $_POST['pays'] : '';
$villes = trouver_sous_index($destinations, $pays);
$suite = is_numeric($item) ? $item : false;
list($mem, $visites)
    = isset($_COOKIE['visite_mem'])
    ? pister_visiteur($suite, $_COOKIE['visite_mem'])
    : pister_visiteur($suite);
if (!is_array($visites)) {
    header('HTTP/1.1 403 Forbidden');
    $body = $visites;
} elseif (!$villes) {
    header("HTTP/1.1 303");
    header("Location: form_pays.php");
} else {
    $titre = "Votre voyage";
    if (is_numeric($item)) {
        $pays = htmlspecialchars($pays, ENT_QUOTES);
        $hidden = "<input type='hidden' name='pays' value='$pays' />";
        $body = html_form(soumission_multiple($villes, $item) . $hidden, 'post');
        $duree = time()+(7*3600*24);
    } else {
        if (isset($villes[$item]))
            $body = "Bon séjour à $item pour " . ($villes[$item] * count($visites)) . "€.";
        else $body = "Ville inconnue";
        $duree = 0;
    }
    setcookie('visite_mem', $mem, array('samesite' => 'Strict', 'expires' => $duree));
    echo debut_html($titre),
        "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
}
?>