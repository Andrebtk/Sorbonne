<?php

// Simulateur SMTP tournant sur le port 5225 de localhost par defaut 

// Boucle de lecture de requetes SMTP d'un client
function emulate_smtp($sock){

    static $queue = array();
	if (!$sock) return '';
    echo "Prise en charge d'un client\n";
	// Message de bienvenue
	socket_write($sock, "220 Simple Mail Transfer Pseudo\n");
	$etape = $from = $data = '';
	$to = array();

	while (true){
		$requete = socket_read($sock,256);
		if (preg_match('/^([A-Z ]+):?\s*(.*?)\s*$/', $requete, $rep)) {
            list(, $next, $parametres) = $rep;
            $next = trim($next);
            echo "$next $parametres\n";
            switch ($next) {
            case "EHLO" :
            case "HELO" :
					if (!strcmp($etape,"")){
						socket_write($sock, "250-Voici mes commandes:\n");
						socket_write($sock, "250-MAIL FROM\n");
						socket_write($sock, "250-RCPT TO\n");
						socket_write($sock, "250-DATA\n");
						socket_write($sock, "250 QUIT\n");
						$etape = "EHLO";
					} else {
						socket_write($sock, "503 Mauvaise sequence de commandes\n");
					}
					break;
						
            case "MAIL FROM" :
					if (!strcmp($etape, "EHLO")){
						if (nom_mail_alors($parametres)){
							socket_write($sock, "250 <" . $parametres . "> Sender OK\n");
                            $from = $parametres;
							$etape = $next;
						} else {
							socket_write($sock, "551 Utilisateur non declare localement\n");	
						}
					} else {
						socket_write($sock, "503 Mauvaise sequence de commandes\n");
					}
					break;
	
            case "RCPT TO" :
					if ((!strcmp($etape,"MAIL FROM"))
                        OR !(strcmp($etape,"RCPT TO"))){
						if (nom_mail_alors($parametres)){
							socket_write($sock, "250 $parametres Destinataire OK\n");
                            $to[]=$parametres;
							$etape = $next;
						} else {
							socket_write($sock, "501 Erreur de syntaxe dans '$parametres'\n");	
						}
					} else {
						socket_write($sock, "503 Mauvaise sequence de commandes\n");
					}
					break;

            case "DATA" :
					if (strcmp($etape,"RCPT TO")) {
						socket_write($sock, "354 Destinaires manquants\n");
                        break;
                    }
                    socket_write($sock, "351 Envoyez. Terminez par un point seul.\n");
                    $cpt = 0;
                    while (rtrim ($ligne = socket_read($sock, 256, PHP_NORMAL_READ)) != '.') {
                        ++$cpt;
                        $data .= $ligne;
                    }
                    echo $cpt . " lignes lues\n";
                    $queue[]= envoiSMTP($from, $to, $data);
                    socket_write($sock, "250 Mail de " . strlen($data) . " octets, envoi numero " . count($queue) . ".\n");
                    $etape = "EHLO";
                    $from = '';
                    $to = array();
					break;
					
            case "QUIT" :
					@socket_write($sock, "221 Fermeture de la connexion\n");
					@socket_close($sock);
					$etape = $next;
					return $queue;
					
            default :
                socket_write($sock, "500 Commande non reconnue $next\n");
                break;
            }
        }
    }
}

function nom_mail_alors($mail){
	return preg_match('/([\w._-]+)@.+$/', $mail, $m) ? $m[1] : '';
}

// Ecrire dans une boite locale
// au format du RFC 4155 alias "man mbox" sur Unix

function envoiSMTP($from, $to, $data)
{
    foreach($to as $mail) {
        $f = '/tmp/' . nom_mail_alors($mail) . '.mbox';
        if ($d = fopen($f, 'a')) {
            fputs($d, "From $from\nDate; "
                  . date('D M m H:n:s Y')
                  . "\nTo: "
                  . join(", ", $to)
                  . "\n\n"
                  . $data
                  . "\n\n");
        } else echo "echec de creation de $f";
    }
    return count($to);
}

$port = !isset($_SERVER["argv"][1])? 5225: $_SERVER["argv"][1];

if (function_exists("date_default_timezone_set")) {
  if (ini_get("date.timezone") =='')
      date_default_timezone_set("Europe/Paris");
}

// Creation d'une socket serveur en attente
$sock = socket_create_listen($port, 5) or die (socket_strerror(socket_last_error()));
echo "Serveur SMTP actif sur le port $port\n";
try {
    while (true) emulate_smtp(socket_accept($sock));
}
catch (Exception $e){}
fclose($sock);
?>
