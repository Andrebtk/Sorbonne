<?php
    include "mails.php";
    include "../TME2/debut_html.php";
    include "rdv.match.php";
    include "rdv.form.php";

    if(isset($_POST['qui'])) {
        $titre = "Reponse";
        var_dump($_POST['qui']); //$a = rdv_match();

        $ind = $_POST['qui'];
        $final = rdv_match($ind, $mails);
        var_dump($final);
        if ($final != array()) {
            foreach($final as $k => $v) {
                echo $k . $v;
            }
        } else {
            $titre = "formulaire";
            $body = rdv_form($mails);
        }

    } else {
        $titre = "formulaire";
        $body = rdv_form($mails);
    }

    echo debut_html($titre) . "<body>" . $body . "</body></html>";


?>