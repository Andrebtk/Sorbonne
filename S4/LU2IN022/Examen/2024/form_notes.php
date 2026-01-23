<?php 

    include '../../TD3/saisie_fiable.php';
    include 'authentifie.php';
    include '../../TME2/debut_html.php';
    include 'phraser.php';
    include 'affiche_notes.php';

    $numero_etudiant = saisie_fiable($_POST, 'numero_etudiant');
    $mot_de_passe =  saisie_fiable($_POST, 'mot_de_passe');
    
    if(!$numero_etudiant AND !$mot_de_passe AND authentifie(trim($_POST['numero_etudiant']), trim($_POST['mot_de_passe']))) {
        $titre = 'ok';
        $body =  affiche_notes(phraser('notes.xml', new sax_notes),trim($_POST['numero_etudiant']));
    } else {
        if(!authentifie($numero_etudiant, $mot_de_passe)){
            header('HTTP/1.1 403');
            $titre = 'erreur Identifiants incorrects';
        }
        $body = "<form action='' method='post'> <fieldset>\n"
                . "<label for='numero_etudiant'>Numero Etudiant:</label><input id='numero_etudiant' name='numero_etudiant' />\n"
                . "<label for='mot_de_passe'>Mot de passe:</label><input id='mot_de_passe' name='mot_de_passe' />\n"
                . "<input type='submit' />"
                . "</fieldset></form>\n";
    }

    echo debut_html($titre) ."<body>\n". $body . "</body></html>";
?>