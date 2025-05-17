<?php 

    include 'phraser.php';
    include 'libmus.liste.php';

    function libmus_table($tab_album) {
        $res = "<table>\n"
                ."<tr class='album'><th>Artiste</th><th colspan='3'>Albums</th></tr>\n" ;
        
        foreach($tab_album['albums'] as $name_alb=>$data){
            $res .= "<tr><td class='artiste'>".$data['artiste']."</td><td class='titre'>$name_alb</td><td>".$data['genre']."</td>"
                . "<td>[+]<ul class='descr'><li>Description: ". $data['descr']."</li><li>Plus d'œuvres du même artiste :".libmus_liste($data['artiste'], $tab_album)."</li></ul></td>"
                . "</tr>\n";
        }

        return $res . "</table>\n";
    }

    echo libmus_table(phraser('libmus.xml', new libmus_sax))

?>