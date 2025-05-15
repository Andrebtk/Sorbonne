<?php
define('DIR_TMP', '/tmp/');

function tmp_file ($alea)
{
    $nom = md5($_SERVER['HTTP_USER_AGENT'] .  $_SERVER['REMOTE_ADDR'] . $alea);
    return "acs_$nom.txt";
}

function pister_visiteur ($val, $nom='')
{
    $contenu = array();
    if ($nom) {
        $f = DIR_TMP . $nom;
        $contenu = is_readable($f) ? unserialize(file_get_contents($f)) : false;
        if ($contenu) {
            if ($nom != tmp_file($contenu[0])) {
                return array($nom, "cookie invalide");
            }
            $contenu[]=$val;
        }
    }
    if (!$contenu) {
        $alea = mt_rand();
        $contenu = array($alea);
        $nom = tmp_file($alea);
        $f = DIR_TMP . $nom;
    }
	if ($val === false) {
        if (file_exists($f)) {unlink($f);}
    } else {
        if (!file_put_contents($f, serialize($contenu))) {
            return array($nom, "Fichier inaccessible");
        }
    }
    array_shift($contenu);
    return array($nom, $contenu);
}
?>
