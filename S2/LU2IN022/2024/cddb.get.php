<?php

    include "cddb.re.php";
    include "cddb.html.php";
    include "cddb.entetes.php";
    include "../TD3/saisie_fiable.php";
    include "../TD3/html_form.php";



    $suite = saisie_fiable($_GET, 'suite', RE_ENTIERS);
    $lang = saisie_fiable($_GET, 'lang',  RE_LANG);
    $titre = 'Formulaire CDDB';

    if (($suite == 0) AND ($lang >= 0) ) {
        
        if ($lang == 1) {
            
            $langBackup = saisie_fiable($_SERVER, 'HTTP_ACCEPT_LANGUAGE', RE_LANG);
            
            if ($langBackup == 0) {
                preg_match(RE_LANG, $_SERVER['HTTP_ACCEPT_LANGUAGE'], $m);
                $l = $m[1];
            } else {
                $l = 'fr';
            }
        } else {
            $l = $_GET['lang'];
        }

        cddb_entetes($_GET['suite'], $l);
        

    } else {

        $preSuite = ($suite < 1) ? $_GET['suite'] : '';
        $body = html_form("<label for='suite'>Suite </label><input name='suite' id='suite' value='" . htmlspecialchars($preSuite) . "' >\n".
            "<input type='submit'>");
        
        $titre = "Erreur - " . $titre;
        echo cddb_html($titre, $body);
    }

   
?>