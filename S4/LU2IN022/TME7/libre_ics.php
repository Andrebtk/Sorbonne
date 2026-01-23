<?php 

    /*
    une date exprimée sous forme d’un nombre de 8 chiffres, indiquant l’année (4 chiffres), le mois et le jour (2 chiffres chaque) ;
    une heure de début sous forme d’une nombre de 6 chiffres, heures, minutes, secondes (2 chiffres chaque) ;
    une heure de fin exprimée pareillement ;
    un agenda ICS sous forme du tableau de ses lignes.
    */
    function libre_ics($d, $hd, $hf, $ics) {
        
        $d = array();

        foreach($ics as $line=>$data){


            if(preg_match('/^DT(START|END);[^:]*:(\d+)T(\d+)/',$data, $m)){
                $d[$m[1]] = $m[3];

                if(count($d) == 2) {
                    if($d['START']<$hd AND $d['END']>$hf AND $d = $m[2]){
                        return false;
                    }
                    $d = array();
                }
            } else if(preg_match('/ END:VEVENT/', $data)) {
                $d = array();

            }
        }


        return fusionne_ics($ics, rdv_ics($d, $hd, $hf));
    }

?>