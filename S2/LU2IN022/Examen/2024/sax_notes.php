<?php 

    include 'class_sax.php';



    class sax_notes implements preneurs_sax {
        
        protected $cours = array();

        protected $last_cours ='';
        protected $last_type_cc = '';
        protected $last_etudiant = '';
        protected $last_balise = '';

        
        function ouvrante ($phraseur, $nom, $attr){
            if($nom == "cours") {
                $this->cours[$attr['code']] = array('nom'=>$attr['nom']);
                $this->last_cours = $attr['code'];
            }

            if($this->last_cours!='' AND ($nom=='partiel' OR $nom=='final' OR $nom=='tp')){
                if(isset($attr['coefficient'])){
                    $this->cours[$this->last_cours][$nom] = array('coefficient'=>$attr['coefficient']);
                }
                else {
                    $this->cours[$this->last_cours][$nom] = array();
                }
                $this->cours[$this->last_cours][$nom]['notes'] = array();
                $this->last_type_cc = $nom;
            }
            
            if($this->last_cours!='' AND $nom == "etudiant"){
                $this->last_etudiant = $attr['numero'];
            }

            $this->last_balise = $nom;
        }

        function fermante ($phraseur, $nom){

        }

        function texte ($phraseur, $texte){
            
            if($this->last_balise == 'etudiant'){
                if(!isset($this->cours[$this->last_cours][$this->last_type_cc]['notes'][$this->last_etudiant])){
                    $this->cours[$this->last_cours][$this->last_type_cc]['notes'][$this->last_etudiant] = trim($texte);
                }
            }
        }

        function retour ($msg){
            return $this->cours;
        }
    }

   
?>