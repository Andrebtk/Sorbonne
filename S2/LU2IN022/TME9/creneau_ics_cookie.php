<?php
include '../TD2/re_jour.php';
include '../TD2/re_heure.php';
include '../TD3/saisie_fiable.php';
include 'debut_html.php';

$jour = saisie_fiable($_POST, 'jour', RE_JOUR);
$fin = saisie_fiable($_POST, 'fin',  RE_HEURE);
$debut = saisie_fiable($_POST, 'debut', RE_HEURE);
// distinguer premier envoi et absence aux suivants pour le TM9
$file = empty($_FILES['ICS']) ? '' :
      (empty($_FILES['ICS']['tmp_name']) ? false : $_FILES['ICS']['tmp_name']);

if (!$file OR $jour OR $debut OR $fin) {
    
    $options = array('samesite' => 'Strict', 'expires' => time()+3600);
    if($jour<0) setcookie("jour","erreur");
    if($fin<0) setcookie("fin","erreur");
    if($debut<0) setcookie("debut","erreur");
    if($file == false) setcookie("ICS","erreur");


    echo debut_html('RDV', array('.erreur {border:2px dashed red}')), "<body onload='class_from_cookie()'>\n";
    include 'creneau.html';
    echo "<script type='text/javascript' src='class_from_cookie.js' ></script></body></html>\n";
} else {
    include 'libre_ics.php';
    include 'envoi_ics.php';
    $cal = libre_ics($_POST['jour'], $_POST['debut'], $_POST['fin'], file($file));
    envoi_ics($cal, $cal ? 'rdv.ics' : 'Pas libre');
}
?>