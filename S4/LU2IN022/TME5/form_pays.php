<?php
    include "destination.php";
    include "tableau_en_select.php";
    include "../TME2/debut_html.php";
    include "../TD3/html_form.php";

    $titre = "Pays";
    $body = tableau_en_select($destinations, 'pays');
    $body = html_form($body . "<input type='submit' />", 'post', 'form_ville_memo_cookie.php');
    echo debut_html($titre), "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
?>