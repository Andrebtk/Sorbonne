<?php

include '../TME2/debut_html.php';
include 'html_form.php';
include 'specialchars_en_table.php';

# Solution avec page HTML complete,
# la reponse demandee remplacerait les 2 dernières lignes par "echo $body".
$titre = "Formulaire avec textarea";
if (isset($_POST['url']) AND isset($_POST['jour'])){
    $body = specialchars_en_table($_POST, "Informations"); 
} else {
    $body = "<label for='jour'>Jour</label> <input id='jour' name='jour' />\n"
          . "<label for='url'>Url</label><textarea id='url' name='url'></textarea>\n";
    $body = html_form($body . "<input type='submit'>", 'post');
}
echo debut_html($titre),
    "<body><div><h1>$titre</h1>\n$body</div></body></html>\n";
?>