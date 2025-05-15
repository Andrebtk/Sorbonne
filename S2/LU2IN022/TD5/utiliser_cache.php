<?php 

    include "trouver_cache.php";
    include "../TME4/requeter_en_http.php";
    include "ignorer_cache.php";
    include "memoriser_cache.php";
    include "fournir_page.php";
    include 'actualiser_cache.php';
    include 'typer_cache.php';



    /// Constante indiquant le nombre maximum de cache
    define('MAX_CACHES', 2);
    /// Répertoire des caches
    define('DIR_CACHE', '/tmp');
    /// Fichier de la table des caches : md5 => date (en secondes depuis le 1/1/1970)
    define('FILE_CACHE', '/tmp/caches');



    if (isset($_GET['url'])) {
        $url = $_GET['url'];
        $md5 = md5($url);
        $reponse = trouver_cache(DIR_CACHE, $md5);
        if (!$reponse) {
            $reponse = requeter_en_http($url);
            if ($reponse[0] != 200
                OR ignorer_cache($reponse[1])
                OR !memoriser_cache(DIR_CACHE, $md5, $reponse[1], $reponse[2])) {
                $md5 ='';
            }
        }
        fournir_page($reponse);
        if ($md5) {
            actualiser_cache ($md5, FILE_CACHE, DIR_CACHE, MAX_CACHES);
        }
    }

?>