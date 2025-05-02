<?php 
    include '../TME6/class_sax.php';
    include 'analyse_dtd.php';

    class sax_validateur_min implements preneurs_sax {

        protected $dtd = array();
        protected $les_erreurs = array();


        function  __construct($chaine){
            if(is_readable($chaine)){
                $this->dtd = analyse_dtd(ile_get_contents($chaine));
            }
        }

        function ouvrante ($phraseur, $nom, $attr){
            if(!isset($this->dtd[$nom])) {
                $this->erreur($phraseur, "Inconue :" . $nom);
            }else {
                $this->controle_attributs($phraseur, $nom, $attr);
            }
        }
        
        function fermante ($phraseur, $nom){ }
        
        function texte ($phraseur, $texte){ }

        function retour ($err){
            return join(" ", $this->les_erreurs);
        }

        function erreur($phraseur, $nom){
            $line = xml_get_current_line_number($phraseur);
            $this->les_erreurs[] = $line . ": " . $nom . '\n';
        }

        function controle_attributs($phraseur, $nom, $attr) {
            $res = array();

            foreach($this->dtd[$nom]["REQUIRED"] as $nom_dtd=>$type_dtd){
                if(!isset($attr[$nom_dtd])){
                    $this->erreur($phraseur, "Manquant :" . $nom);
                }else {
                    $res[$nom_dtd] = $type_dtd;
                    unset($attr[$nom_dtd]);
                }
            }

            foreach($attr as $att=>$val){
                if(isset($this->dtd[$nom]["IMPLIED"][$att])){
                    $res[$nom_dtd] = $type_dtd;
                    unset($attr[$nom_dtd]);
                }  
            }


            if($attr) {
                $this->erreur($phraseur, "Inconue:" . join(" ", array_keys($attr)));
            }
        }
    }
    
?>