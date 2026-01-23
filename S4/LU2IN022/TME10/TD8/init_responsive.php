<?php
function init_responsive ($urls, $choix)
{
    $tab = array();
    foreach($choix as $medium => $numero)
    {
        if (isset($urls[$numero])) {
            $tab[] = array('href' => $urls[$numero], 'media' => $medium);
            // variante:  $tab[$medium] = array('href' => $urls[$numero]);
        }
   }
    return $tab;
}
?>