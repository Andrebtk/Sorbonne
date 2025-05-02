<?php 

    include 'sax_table.php';

    class sax_input extends sax_table {

        protected $tab = array();

        function ouvrante ($phraseur, $nom, $attr) {
            if($nom=="input" && isset($attr['name'])) {

                if(!isset($attr['id'])) {
                    $attr['id'] = $attr["name"];
                }

                if(!isset($this->tab[$attr['id']])){
                    $this->tab[$attr['id']] = "<label for='" . $attr['id'] 
                        . "'>" . $attr['id'] . "</label>";
                }
            }

            if($nom == "label") {
                if(isset($attr['for'])){
                    $this->tab[$attr['for']] = "";
                }
            }
            parent::ouvrante($phraseur, $nom, $attr);
        }


        function fermante ($phraseur, $nom) {
            
            if($nom == "form") {
                echo join(" ", $this->tab);
                $this->tab = array();
            }


            parent::fermante($phraseur, $nom);
        }




    }

    //phraser('test.html', new sax_input);
?>