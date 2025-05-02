<?php
    include 'sax_echo.php';

    class sax_table extends sax_echo {
        protected $tr = 0;

        function ouvrante ($phraseur, $nom, $attr) {
            if($nom == "tr"){
                $this->tr++;
            }
            if($nom == "td" AND $this->tr == 1) {
                $nom = "th";
            }

            parent::ouvrante($phraseur, $nom, $attr);
        }

        function fermante ($phraseur, $nom) {
            if($nom == "td" AND $this->tr == 1) {
                $nom = "th";
            }

            if($nom == "table"){
                $this->tr = 0;
            }
            
            parent::fermante($phraseur, $nom);
        }
    }

    //phraser('test.html', new sax_table);
?>