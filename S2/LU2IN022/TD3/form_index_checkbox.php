<?php 
include '../TME2/debut_html.php';
include '../TD2/tableau_en_liste.php';
include 'html_form.php';
include 'tableau_pour_cocher.php';

$villes = array('Paris', 'Lyon', 'Marseille'); // pour essai
if (!isset($_GET['choix']) OR !is_array($_GET['choix'])) {
    $titre = "Possibilités";
    $body = tableau_en_liste(tableau_pour_cocher($villes, 'choix'));
    $body = html_form($body . "<input type='submit' />");
} else {
    $titre = "Choix effectués";
    $final = array();
    // Ne pas faire confiance aux valeurs transmises, repartir des index
    foreach ($_GET['choix'] as $n => $v) $final[] = $villes[$n];
    $body = tableau_en_liste($final);
}
echo debut_html($titre),
    "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
?>