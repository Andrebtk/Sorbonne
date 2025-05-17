<?php 
include '../TME2/debut_html.php';
include '../TD2/tableau_en_liste.php';
include '../TD3/html_form.php';
include '../TD3/tableau_pour_cocher.php';

$villes = array('Paris', 'Lyon', 'Marseille'); // pour essai
if (!isset($_GET['choix']) OR !is_array($_GET['choix'])) {
    $titre = "Possibilités";

    header("Content-Type: text/plain");
    foreach($_GET['choix'] as $n => $v){
        echo $villes[$n] . "\n";
    }
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