<?php
interface preneurs_sax
{
    function ouvrante ($phraseur, $name, $attrs) ;
    function fermante ($phraseur, $name);
    function texte    ($phraseur, $texte);
    function retour   ($msg);
}
?>
