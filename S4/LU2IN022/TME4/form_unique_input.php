<?php 
   include "../TD3/specialchars_en_table.php";
   include "requeter_en_http.php";
   include "../TME2/debut_html.php";
   include "../TD3/html_form.php";

   $titre = "Visualisation des en-têtes";
    if (!isset( $_GET['url'])) {
        $body = "<label for='url'>URL</label> <input id='url' name='url' size='99'/>";
        $body = html_form($body);
    } else {
        list($status, $entetes,) = requeter_en_http($_GET['url'], 'HEAD', '1.0');
        $t = htmlspecialchars($_GET['url']) . " status $status";
        $body = specialchars_en_table($entetes, $t);
    }
    echo debut_html($titre), "<body>$body</body></html>\n";


?>