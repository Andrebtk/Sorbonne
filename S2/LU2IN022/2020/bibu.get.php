<?php

    include "bibu.form.php";
    include "bibu.re.php";
    include "../TD3/saisie_fiable.php";
    include "../TME2/debut_html.php";

    $a  = saisie_fiable($_POST, "auteur", RE_BIBU);
    echo debut_html( (($a == false)? "Erreur" : ""). "Multilingue")
        .   "<body>";

    $a = saisie_fiable($_GET, 'auteur', RE_AUTEUR);
    echo debut_html(($a === False ? 'Erreur ': '') . 'Multilingue'), "<body><div>\n";
    if ($a) {
        include 'bibu.socket.php';
        include 'bibu.table.php';
        include 'bibliotheques.php';
        echo bibu_table(bibu_socket($bibliotheques, $_GET['auteur']));
    } else {
        include 'bibu.form.php';
        if ($a === false) echo "<h1>Erreur de saisie</h1>\n";
        echo bibu_form($a === false ? $_GET['auteur'] : '');
    }
    echo "</div></body></html>";

    echo "</body></html>";
?>