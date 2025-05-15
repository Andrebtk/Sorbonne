<?php 
    include "../TD2/re_entete.php";


    /// Lire les entetes jusqu'a rencontre d'une ligne vide
    /// le cas ou preg_match retourne False signale un entete sur plusieurs lignes
    /*
    function lire_entetes ($sock) {
        /// cette variable contiendra le nom de l'en-tete a l'iteration precedente
        /// afin de realiser une concatenation si la valeur occupe plus d'une ligne
        $cle = '';
        $entetes = array();
        while (trim($ligne = fgets($sock))) {
            if (preg_match(RE_ENTETE, $ligne, $r)){
            $cle = $r[1];
            if (!isset($entetes[$cle])){
                $entetes[$cle] = array($r[2]);
            } else {
                $entetes[$cle][] = $r[2];
            }              
            } else {
                /// Autre ligne : ajout a la derniere cle trouvee
                $entetes[$cle][count($entetes[$cle])-1] .= $ligne;
            }
        }
        return $entetes;
    }
    */

    function lire_entetes ($sock) {
    /// cette variable contiendra le nom de l'en-tete a l'iteration precedente
    /// afin de realiser une concatenation si la valeur occupe plus d'une ligne
    $cle = '';
    $entetes = array();
    while (trim($ligne = fgets($sock))) {
        if (preg_match(RE_ENTETE, $ligne, $r)){
            $cle = $r[1];
            if (!isset($entetes[$cle])){
                $entetes[$cle] = array($r[2]);
            } else {
                $entetes[$cle][] = $r[2];
            }              
        } else {
            /// Autre ligne : ajout a la derniere cle trouvee
            $entetes[$cle][count($entetes[$cle])-1] .= $ligne;
        }
    }
    return $entetes;
    }
?>