<?php
/// Exemple: afficher la profondeur d'imbrication et retourner son maximum
include "class_sax.php";
class sax_prof implements preneurs_sax
{
    protected $prof = 0;
    protected $max = 0;
    function ouvrante ($phraseur, $nom, $attr)
	    {echo "\n", ++$this->prof, " <$nom>"; $this->max = max($this->max, $this->prof);}
    function fermante ($phraseur, $nom)
	    {echo "\n", $this->prof--, " </$nom>";}
    function texte ($phraseur, $texte)
    	{if (trim($texte)) echo "\n", $this->prof, " $texte";}
    function retour ($err)
	    {echo "\n"; return $err ? $err : $this->max;}
}
?>