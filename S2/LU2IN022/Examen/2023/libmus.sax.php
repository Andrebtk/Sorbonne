<?php 
    include 'class_sax.php';

    class libmus_sax implements preneurs_sax {
        protected $tab = array('albums'=>array(), 'artistes'=>array());

        protected $last_alb = '';
        protected $last_art = '';

        protected $last_balise = '';

        function ouvrante ($phraseur, $name, $attrs) {
            if($name == 'album'){
                $this->tab['albums'][$attrs['id']]=array(
                    'artiste' => $attrs['artiste'],
                    'annee' => $attrs['annee']
                );
                $this->last_alb = $attrs['id'];
            }

            if($name == 'artiste'){
                $this->tab['artistes'][$attrs['id']] = array();
                $this->last_art = $attrs['id'];
            }


            $this->last_balise = $name;

        }

        function fermante ($phraseur, $name) {
            if($name == 'album'){
                $this->last_alb = '';
            }

            if($name == 'artiste'){
                $this->last_art = '';
            }
        }

        function texte    ($phraseur, $texte) {
            if($this->last_alb && (($this->last_balise == 'titre') ||($this->last_balise == 'genre') || ($this->last_balise == 'descr'))){
                if(!isset( $this->tab['albums'][$this->last_alb][$this->last_balise])) {
                    $this->tab['albums'][$this->last_alb][$this->last_balise] = trim($texte);
                }
            }


            if($this->last_art && (($this->last_balise == 'nom') || ($this->last_balise =='contact'))){
                if(!isset( $this->tab['artistes'][$this->last_art][$this->last_balise])) {
                    $this->tab['artistes'][$this->last_art][$this->last_balise] = trim($texte);
                }
            }
        }

        function retour   ($msg) {
            return $this->tab;
        }
    }

?>