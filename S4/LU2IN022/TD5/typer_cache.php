<?php
/// la valeur de Content-Type, outre des espaces initiaux, est formee
/// du nom de la famille du document (text, image etc) suivi d'un "/"
/// puis type du document (html, gif etc)
/// ce type s'arrêtant au premier caractère non alphanumérique
/// ("+" pour +xml etc, ";" pour un paramètre, séparateur ....)
define('RE_CONTENT_TYPE', ",/(\w+),");

function typer_cache ($headers)
{
    if (isset($headers['Content-Type'])
    AND preg_match(RE_CONTENT_TYPE, $headers['Content-Type'][0], $m))
      return $m[1];
    return 'html';
}
/*// Test
if (preg_match(RE_CONTENT_TYPE, 'text/ics;charset=utf-8', $m)) echo $m[1], "\n";
if (preg_match(RE_CONTENT_TYPE, 'img/svg+xml', $m)) echo $m[1], "\n";
if (preg_match(RE_CONTENT_TYPE, 'audio/mp3', $m)) echo $m[1], "\n";
if (preg_match(RE_CONTENT_TYPE, 'multipart/mixed ;boundary="PHOTE DAURTAUGRAF"', $m)) echo $m[1], "\n";
//*/
?>