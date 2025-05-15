<?php
    include "../TME2/re_url.php";
    include "../TD2/re_jour.php";
    include "saisie_fiable.php";
    include "../TME2/debut_html.php";
    include 'html_form.php';
    include 'specialchars_en_table.php';

    $url = saisie_fiable($_POST, 'url', RE_URL);
    $jour = saisie_fiable($_POST, 'jour', RE_JOUR);
    $titre = "Evénement";
    $err = '';
    if (!$url AND !$jour) {
        $body = specialchars_en_table($_POST, "Informations");
    } else {
        if ($url < 0) $err = ' url';
        $url = ($url > 0) ? '' : htmlspecialchars($_POST['url'], ENT_QUOTES);
        if ($jour < 0) $err .= ' jour';
        $jour = ($jour > 0) ? '' : htmlspecialchars($_POST['jour'], ENT_QUOTES);
        if ($err) $titre = "Erreur $err $titre"; 
        $body = "<label for='jour'>Jour :</label>" .
            "<input id='jour' name='jour' value='$jour' />\n" .
            "<label for='url'>Url :</label>" .
            "<textarea id='url' name='url'>$url</textarea>\n";
        $body = html_form($body . "<input type='submit'>", 'post');
    }

    echo debut_html($titre),
        "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
    
?>