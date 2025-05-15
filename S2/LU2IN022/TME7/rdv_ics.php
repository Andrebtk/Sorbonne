<?php 
    /*
    une date exprimée sous forme d’un nombre de 8 chiffres, indiquant l’année (4 chiffres), le mois et le jour (2 chiffres chaque) ;
    une heure de début sous forme d’une nombre de 6 chiffres, heures, minutes, secondes (2 chiffres chaque) ;
    une heure de fin optionnelle exprimée pareillement ;
    un nom d’événement sous forme d’une chaîne de caractères, également optionnel.
    */
    function rdv_ics($d1, $hd, $hf=0, $nom='') {
        $res = array();
        $res[] = "BEGIN:CALENDAR";
        $res[] = "BEGIN:VEVENT";
        $res[] = "DTSTART:$d1"."T$hd";
        
        if($hf != 0) {
            $res[] = "DTEND:$d1"."T$hf";
        }
        if($nom){
            $res[] = "DESCRIPTION:$nom";
        }


        $res[] = "END:VEVENT";
        $res[] = "END:VCALENDAR";

        return $res;
    }
    var_dump(rdv_ics(20240118,160000,180000, 'HELLO THERE'));


?>