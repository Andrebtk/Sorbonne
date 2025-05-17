<?php

// Simulateur POP tournant sur le port 2110 de localhost par defaut 
// Ce simulateur ne fait qu'accepter les commandes de base
// et y repondre par les codes de retour habituels, mais en fait rien.

include 'webmail.auth.php';

// Boucle de lecture de requetes SMTP d'un client
function emulate_pop($sock){

    static $queue = array();
	if (!$sock) return '';
    echo "Prise en charge d'un client\n";
	// Message de bienvenue
	socket_write($sock, "+OK\n");
	$pass = $user = '';

	while (true){
		$requete = socket_read($sock,256);
		if (preg_match('/^(\w+)\s*(.*?)\s*$/', $requete, $rep)) {
            list(, $next, $parametres) = $rep;
            echo $requete;
            switch ($next) {
            case "STAT" :
                if (!$pass) {
                    socket_write($sock, "-ERR\n");
                } else {
                    socket_write($sock, "+OK 3 140\n");
                }
                break;
            case "RETR" :
				envoi_pop($sock, $parametres);
                break;
            case "USER" :
                $user = $parametres;
                socket_write($sock, "+OK\n");
                break;
            case "PASS" :
                $pass = $parametres;
                if ($user AND webmail_auth($user, $pass))
                    socket_write($sock, "+OK\n");
                else {
                    $pass = '';
                    socket_write($sock, "-ERR\n");
                }
                break;
            case "QUIT" :
					@socket_write($sock, "+OK Fermeture de la connexion\n");
					@socket_close($sock);
					return $queue;
					
            default :
                socket_write($sock, "-ERR Commande non reconnue $next\n");
                break;
            }
        }
    }
}

// simulation d'une boite aux lettres par un tableua
// chaque element est un mail
// chaque mail est un tableau de lignes

function envoi_pop($sock, $n)
{
    static $mbox = array(array(),
                         array('From: foo@bar.net', 'Date: 14/3/2022', '', 'rien'),
                         array('From: bar@foo.net', 'Date: 12/2/2022', '', 'vide'),
                         array('From: bar@foo.net', 'Date: 12/1/2022', '', 'bof')
    );
    if (empty($mbox[$n]))
        socket_write($sock, "-ERR\n");
    else {
        socket_write($sock, "+OK\n");
        foreach($mbox[$n] as $l) socket_write($sock, "$l\n");
        socket_write($sock, ".\n");
    }
}

$port = !isset($_SERVER["argv"][1])? 2110: $_SERVER["argv"][1];

if (function_exists("date_default_timezone_set")) {
  if (ini_get("date.timezone") =='')
      date_default_timezone_set("Europe/Paris");
}

// Creation d'une socket serveur en attente
$sock = socket_create_listen($port, 5) or die (socket_strerror(socket_last_error()));
echo "Pseudo serveur POP actif sur le port $port\n";
while (true) emulate_pop(socket_accept($sock));
?>
