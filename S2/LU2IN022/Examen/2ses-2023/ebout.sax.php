<?php 
    include 'class_sax.php';


    class ebout_sax implements preneurs_sax {

        protected $categories = array();
        protected $articles = array();
        
        protected $art = false;
        protected $arr_genre = array();
        protected $arr_motclef = array();
        protected $last_cat = "";
        protected $last_art = "";
        protected $last_bal = "";

        function ouvrante ($phraseur, $name, $attrs) {
            if($name == "categorie") {
                $this->categories[$attrs["id"]] = $attrs['libelle'];
                $this->last_cat = $attrs["id"]; 
            }

            if($name == "article"){
                $this->art = true;
                $this->articles[$attrs['id']] = array('prix'=>$attrs['prix'], 
                                                        'categorie'=>$this->last_cat,
                                                        'genre'=>array(),
                                                        'mot-clef'=>array()
                                                    );
                $this->last_art = $attrs['id'];
            }
            
            if($name == "media" AND $this->art){
                $this->articles[$this->last_art]['media'] = $attrs['url'];
            }

            
            

            $this->last_bal = $name;
        }

        function fermante ($phraseur, $name){
            $this->last_bal = "";
        }

        function texte ($phraseur, $texte) {
            if($this->last_bal == "genre" AND $this->art) {
                $this->articles[$this->last_art]['genre'][] = $texte;
            }

            if($this->last_bal == "mot-clef" AND $this->art) {
                 $this->articles[$this->last_art]['mot-clef'][] = $texte;
            }

            if($this->last_bal == "description" AND $this->art) {
                $this->articles[$this->last_art]['description'] = $texte;
            }
        }

        function retour ($msg) {
            return array($this->categories, $this->articles);
        }

    }

?>