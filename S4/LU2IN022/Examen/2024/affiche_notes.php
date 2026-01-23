<?php 

    
    function affiche_notes($notes, $num_etudiant) {
        $res = "<table>\n"
                
                ."<tr><th>nom du cours</th><th>Partiel</th><th>Final</th><th>TP</th><th>moyenne</th></tr>\n";

        foreach($notes as $UE=>$data){
            //echo $UE . "\n" . var_dump($data);
            $nom_cours = $data['nom'];
            $t=0;

            $note_partiel = (isset($data['partiel'])) ? $data['partiel']['notes'][$num_etudiant]: '-';
            $coef_partiel = (isset($data['partiel']['coefficient'])) ? $data['partiel']['coefficient']: 0;
            if($note_partiel!='-') $t++;

            $note_final = (isset($data['final'])) ? $data['final']['notes'][$num_etudiant]: '-';
            $coef_final = (isset($data['final']['coefficient'])) ? $data['final']['coefficient']: 0;
            if($note_final!='-') $t++;

            $note_tp = (isset($data['tp'])) ? $data['tp']['notes'][$num_etudiant]: '-';
            $coef_tp = (isset($data['tp']['coefficient'])) ? $data['tp']['coefficient']: 0;
            if($note_tp!='-') $t++;
            
            $moy = ($note_final + $note_partiel + $note_tp) /$t; //(($note_final*$coef_partiel + $note_partiel* $coef_final + $note_tp* $coef_tp) / (20*$coef_partiel + 20*$coef_final+ 20*$coef_tp)) *20 ;
            $res .= "<tr><td>$nom_cours</td><td>$note_partiel</td><td>$note_final</td><td>$note_tp</td><td>$moy</td></tr>\n";
        
        }

        return $res ."<script src='notes.js'></script>\n". "</table>\n";
    }

?>