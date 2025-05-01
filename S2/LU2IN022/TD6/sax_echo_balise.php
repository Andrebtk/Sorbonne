<?php
    include "../TME6/phraser.php";
    include "../TME6/class_sax.php";

    class sax_echo_balise implements preneurs_sax {
        
        function ouvrante ($phraseur, $nom, $attr){
            echo "<div style='color:red'>Ouverture de :</div>";
            echo $nom . "<br />";            
        

            echo "\n";
        }
        
        function fermante ($phraseur, $nom){
            echo "<div style='color:green'>Fermeture de :</div>";
            echo $nom . "<br />";    
        }
        
        function texte ($phraseur, $texte){
            echo "Text: $texte \n";
        }

        function retour ($err){
            echo "ERROR: $err \n";
        }
    }

    echo phraser('carnet.xml', new sax_echo_balise);


?>