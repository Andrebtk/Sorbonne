<?php
/// Ce script a été concu en ecrivant ses lignes dans cet ordre:
/// 1 2 3 4 5 6 8 9 10 7 11 12 13 10 14 15 16 17 18 19 20 21 22
include 'debut_html.php';
include 'init_responsive.php';
include 'choisir_style.php';

$styles = array('all.css','all2.css','handheld.css','print.css','screen.css');
$media = array('all', 'print', 'screen', 'handheld');
$choix = array();
foreach($media as $medium) {
    if (!isset($_POST[$medium])) {
        $choix[$medium] = isset($_COOKIE[$medium]) ? $_COOKIE[$medium] : 0;
    } else {
        $choix[$medium] = $_POST[$medium];
        setcookie($medium, $_POST[$medium], array('samesite' => 'Strict'));
    }
}
$links = init_responsive($styles, $choix);
echo debut_html('edt', $links);
echo "<body><h1>edt</h1>";
echo choisir_style($styles, $media, $choix);
include 'edt.html';
/// Une ligne pour le TME 10
echo "<script type='text/javascript' src='../choisirStyle.js'></script>";
echo "</body></html>\n";
?>
