<?php 
    include "annexe_cochemail.php";
    include "cochemail_lang.php";
    include "cochemail_form.php";
    include "cochemail_re.php";
    include "../TME2/debut_html.php";
    include "../TD3/saisie_fiable.php";
    /*
    $tableau_lib = cochemail_lang($libelles, $_SERVER['HTTP_ACCEPT_LANGUAGE']);
    $valide = ((preg_match(RE_UN_MAIL, tableau_lib['moi'])) 
        AND (preg_match('/\w{10,}/', tableau_lib['blabla'])) 
        AND ($tableau_lib['dest'] != array()));
    

    if ($valide) {
        echo "DONE";
    } else {
        echo debut_html("Formulaire")."<body>";

        echo cochemai_form($tableau_lib, $carnet, )
    }
    */

    $dico = cochemail_lang($libelles, $_SERVER['HTTP_ACCEPT_LANGUAGE']);
    $moi = saisie_fiable($_POST, 'moi', RE_UN_MAIL);
    $blabla = saisie_fiable($_POST, 'blabla', '/.{10}/');
    $dest = (isset($_POST['dest']) AND is_array($_POST['dest'])) ? $_POST['dest'] : '';
    if ($moi AND $blabla AND $dest) {
        cochemail_status($dico, $moi, $blabla, $dest);
    } else {
        $body = cochemail_form($dico,
                            $carnet,
                            isset($_POST['dest']) ? $_POST['dest'] : array(),  
                            isset($_POST['moi']) ? $_POST['moi'] : '',
                            isset($_POST['blabla']) ? $_POST['blabla'] : '');
        echo debut_html('Mailing'), "<body>", $body, "</body></html>\n";
    }
?>