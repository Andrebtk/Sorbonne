<?php
include '../TME2/debut_html.php';
include "../TD3/specialchars_en_table.php";
include 'choisir_message_pop.php';
include 'ouvrir_session_pop.php';
include 'fermer_session_pop.php';

function presenter_message_pop ($sock, $criteres)
{
    $rep = choisir_message_pop($sock, $criteres);
    $res = '';
    foreach ($rep as list($n, $entetes, $corps))
    {
        $res .= "<fieldset>"
             . specialchars_en_table($entetes, "Mail $n")
             . "<div>"
             . preg_replace("@\n@s", "<br />\n", htmlspecialchars($corps))
             . "</div></fieldset>\n";
    }
    return debut_html("Mails")
        . "<body>"
        . tableau_en_table($criteres, "criteres")
        . "<div>" . count($rep) . " messages trouvés " . "</div>"
        . $res
        . "</body></html>"; 
  }

/// Test
$sock = ouvrir_session_pop('127.0.0.1', 'moi', '123456789', 2110);
if (is_string($sock))
    echo $sock;
else {
    echo presenter_message_pop($sock,
            array("From" => "maman@ici.fr", "Subject" => "Noel"));
    fermer_session_pop($sock);
}
//*/
?>