<?php 
    include 'sax_input.php';


    class sax_href extends sax_input {
        protected $last_text = "";
        protected $last_href = "";
        protected $tab = array();

        function ouvrante ($phraseur, $nom, $attr) {
            
            echo $this->last_text;
            $this->last_text = '';
            if(($nom == 'a') AND (isset($attr['href']))){
                $this->last_href = $attr['href'];
            }


            parent::ouvrante($phraseur, $nom, $attr);
        }


        function fermante ($phraseur, $nom) {

            if($nom == "a" AND $this->last_href) {
                if(isset($this->tab[$this->last_href])){
                    echo $this->tab[$this->last_href];
                    $this->last_text = "";
                }
                else {
                    $i = 1;
                    if (!in_array($this->last_text, $this->tab)) {
                        $this->tab[$this->last_href] =  $this->last_text;
                    } else {
                        while(in_array($this->last_text.$i, $this->tab)) {
                            $i+=1;
                        }
                        $this->tab[$this->last_href] =  $this->last_text;
                    }
                }
            }

            echo $this->last_text, "</$nom>";
            $this->last_text = '';

        }


        function texte ($phraseur, $texte) {
            $this->last_text = $texte;
        }

    }

    phraser('test.html', new sax_href);
?>