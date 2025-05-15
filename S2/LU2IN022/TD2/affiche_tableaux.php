<?php
    /// 1.
    $Candidats = array("Bob","Alice","Chris");

    /// 2. 1
    echo "<h1>Liste avec for</h1>\n<ul>\n";
    for ($i =0; $i<count($Candidats); $i++) {
    echo "<li>", $Candidats[$i], "</li>\n";
    }
    echo "</ul>\n";
    
    /// 2. 2  
    echo "<h1>Liste avec foreach</h1>\n<ul>\n";
    foreach ($Candidats as $elt) {
    echo "<li>", $elt, "</li>\n" ;
    }
    echo "</ul>\n";


    /// 2. 3
    echo "<h1>Liste avec while</h1>\n<ul>\n";
    while ($Candidats) {
        echo "<li>", array_shift($Candidats), "</li>\n";
    }
    echo "</ul>\n";


    //3.
    /// La fonction asort conservant la relation entre une valeur et son index
    /// l'usage de For provoquera l'affichage dans l'ordre d'origine,
    /// tandis que Foreach et while/array_shift afficheront par ordre alphabetique.

    //4.
    $Scores = array("Alice"=>130,"Bob"=>300,"Chris"=>30);

    /// 5.
    arsort($Scores);
    echo "<h1>Liste num&eacute;rot&eacute;e avec foreach</h1>\n<ol>\n";
    foreach ($Scores as $key => $val) {
    echo "<li>", $key, ": ", $val, "</li>\n" ;
    }
    echo "</ol>\n";

?>