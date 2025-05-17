<?php 

    include 'phraser.php';
    
    header('Content-Type: text/plain');
    if(!isset($_POST['cours'])){
        echo "<p>manque la saisie cours</p>";
    } else {
        $cours = $_POST['cours'];
        $notes = phraser('notes.xml', new sax_notes);

        if(!isset($_POST['evaluation'])){
            $res = "<select name='evaluation'>";
            if(isset($notes[$cours]['partiel'])){
                $res .= "<option>partiel</option>";
            }

            if(isset($notes[$cours]['final'])){
                $res .= "<option>final</option>";
            }

            if(isset($notes[$cours]['tp'])){
                $res .= "<option>tp</option>";
            }
            echo $res . "</select>";
        }
        else {
            $eval = $_POST['evaluation'];

            echo "<table>\n"
                . "<tr><th>nom Evaluation</th><th>Nom cours</th></tr>"
                . "<tr><td>$eval</td><td>$cours</td</tr>"
                . "</table>";
        }
    }


?>