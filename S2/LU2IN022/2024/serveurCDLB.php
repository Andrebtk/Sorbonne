<?php
// Boucle de lecture de requetes d'un client
function cddlb($port, $bd){
    static $connexions = 0;
    if (!preg_match('@^[\w.]+$@', $bd) OR !is_readable($bd))
        die("Base de données '$bd' invalide");
    include $bd;
    if (!isset($CDDLB))
        die("Base de données '$bd' non conforme");
    $public = socket_create_listen($port, 5)
          or die (socket_strerror(socket_last_error()));
    echo "Serveur CDLB actif sur le port $port, " . count($CDDLB) . " entrées en base.\n";
    while (true) {
        $sock = socket_accept($public);
        if (!$sock)
            echo "connexion impossible\n";
        else {
            ++$connexions;
            echo "***Ouverture de la connexion $connexions\n";
            // Message de bienvenue
            socket_write($sock, "220 Compact Disc Language Base\n");
            $requete = socket_read($sock,256, PHP_NORMAL_READ);
            if (!preg_match('/^DISC\s+([1-9]\d*(?:\s+[1-9]\d*)*)(\s-[1-9])?\s*$/',
                            $requete,
                            $req)) {
                $res = "400\n\nBad Request\n";
            } else {
                $langs = array('fr');
                while (strlen ($l = socket_read($sock, 256, PHP_NORMAL_READ)) > 2) {
                    if (preg_match('/^Accept-Language:\s+(.*)/', $l, $m)) {
                        $langs = preg_split('/\W+/', $m[1]);
                    }
                }
                $res = cdlb_find($CDDLB, $req[1], $req[2]??'', $langs);
            }
            echo "Envoi:\n$res\n";
            socket_write($sock, $res);
            echo "***Fermeture la connexion $connexions\n";
            socket_close($sock);
        }
    }
}

function cdlb_find($cdlb, $signature, $choix, $langs)
{
    if (empty($cdlb[$signature]))
        return "404\nContent-Type: text/plain\n\nCompact Disk '$signature' inconnu";
    $selection = $cdlb[$signature];
    if (count($selection) == 1)
        // pas de collision
        return cdlb_choix($signature, $choix, $selection[0], $langs);
    else {
        $n = $choix ? ((0-$choix)-1) : -1;
        if (isset($selection[$n]))
            // leve la collision
            return cdlb_choix($signature, $choix, $selection[$n], $langs);
        foreach($selection as $k => $disk) {
            // On cherche le titre dans la premiere langue fournie
            // c'est à améliorer, et il faudrait le mettre en Quoted-Printable
            $t = $disk[$langs[0]] ?? current($disk);
            $selection[$k] = "Article-Names: " . $t[1];
        }
        $selection[] = "Content-Type: text/plain";
        $selection = join("\n", $selection);
        $choix = $choix ? " $choix" : '';
        return "202\n$selection\n\n$signature$choix\n";
    }
}

function cdlb_choix($signature, $choix, $disk, $langs)
{
    static $ct = "Content-Type: text/plain";
    foreach($langs as $lang) {
        if (isset($disk[$lang])) {
            $d = $disk[$lang];
            $c = array_shift($d);
            $d = join("\n", $d);
            return "200\nContent-Language: $lang\n$ct;charset=$c\n\n$d\n";
        }
    }
    foreach($disk as $l => $v) {$disk[$l] = "Content-Language: $l";}
    return "207\n$ct\n" . join("\n", $disk) . "\n\n$signature$choix\n";
}

cddlb(!isset($_SERVER['argv'][1])? 8080 : $_SERVER['argv'][1],
      !isset($_SERVER['argv'][2])? 'descriptionCDLB.php' : $_SERVER['argv'][2]
);
?>
