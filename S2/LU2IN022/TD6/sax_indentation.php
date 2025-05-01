<?php 


    include "../TME6/phraser.php";
    include "../TME6/class_sax.php";

    
    class sax_prof implements preneurs_sax {

        protected $prof = 0;
        protected $max = 0;
        protected $gt = "";


        function ouvrante ($phraseur, $nom, $attr){
           
            echo $this->gt;

            echo "\n", str_repeat("    ",$this->prof), " <$nom";
            foreach ($attr as $k=>$v) {
                echo " $k='$v'" ;
            }
            
            
            $this->gt = ">";
            $this->prof++;
            $this->max = max($this->max, $this->prof);
        }

        function fermante ($phraseur, $nom){ 
            $this->prof--;
            if($this->gt) {
                echo " />";
                $this->gt = "";
            } else {
                echo "\n", str_repeat("    ",$this->prof), " </$nom>";
            }
        }
        
        function texte ($phraseur, $texte) {
            echo $this->gt;
            $this->gt = "";
            if (trim($texte)) 
                echo "\n", str_repeat("    ",$this->prof), " $texte";
        }

        function retour ($err) {
            echo "\n"; 
            return $err ? $err : $this->max;
        }
    }

    echo phraser('carnet.xml', new sax_prof);
?>