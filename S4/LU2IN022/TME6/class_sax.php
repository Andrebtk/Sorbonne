<?php
interface preneurs_sax
{
    function ouvrante ($phraseur, $nom, $attr);
    function fermante ($phraseur, $nom);
    function texte ($phraseur, $texte);
    function retour ($err); // sert à retourner le résultat final ou les erreurs
}
?>