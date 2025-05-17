<?php 


    function libmus_liste($nom_artiste, $tab) {
        $res = "<ol>\n";
        foreach($tab['albums'] as $nom_album=>$v) {
            if($v['artiste'] == $nom_artiste){
                $res .= '<li>'.$nom_album."</li>\n";
            }

        }
        return $res . "</ol>\n";
    }

    //echo libmus_liste('Foals', phraser('libmus.xml', new libmus_sax))

?>