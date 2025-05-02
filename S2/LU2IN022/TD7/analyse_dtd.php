<?php 
    include 're_dtd.php';
    function analyse_dtd($chaine) {
        $res = array();
        
        if(preg_match_all(RE_DTD_ELEMENT, $chaine, $m, PREG_SET_ORDER)){
            foreach($m as list(,$nom, $content)) {
                $res[$nom] = array(
                    "C" => $content, "REQUIRED" => array(), "IMPLIED" => array()
                );
            }
        }

        if(preg_match_all(RE_DTD_ATTLIST, $chaine, $m, PREG_SET_ORDER)){
            foreach($m as list(,$nom, $att)) {
                if(preg_match(RE_DTD_ATTRIBUTE, $att, $k)){
                    $res[$nom][$k[3]][$k[1]] = $k[2]; 
                }
            }
        }
        return $res;
    }
    var_dump(analyse_dtd(file_get_contents('carnet.dtd')));
    /*

    array(10) {
  ["carnet"]=>
  array(3) {
    ["C"]=>
    string(7) "(ami)* "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["ami"]=>
  array(3) {
    ["C"]=>
    string(43) "(civilite?, nom, mail*, adresse*, mobile*) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["adresse"]=>
  array(3) {
    ["C"]=>
    string(20) "(rue, ville, pays?) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(1) {
      ["telephone"]=>
      string(5) "CDATA"
    }
  }
  ["mobile"]=>
  array(3) {
    ["C"]=>
    string(8) "(EMPTY) "
    ["REQUIRED"]=>
    array(1) {
      ["telephone"]=>
      string(5) "CDATA"
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["mail"]=>
  array(3) {
    ["C"]=>
    string(10) "(#PCDATA) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["civilite"]=>
  array(3) {
    ["C"]=>
    string(10) "(#PCDATA) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["nom"]=>
  array(3) {
    ["C"]=>
    string(10) "(#PCDATA) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["pays"]=>
  array(3) {
    ["C"]=>
    string(10) "(#PCDATA) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["rue"]=>
  array(3) {
    ["C"]=>
    string(10) "(#PCDATA) "
    ["REQUIRED"]=>
    array(0) {
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
  ["ville"]=>
  array(3) {
    ["C"]=>
    string(10) "(#PCDATA) "
    ["REQUIRED"]=>
    array(1) {
      ["codepostal"]=>
      string(5) "CDATA"
    }
    ["IMPLIED"]=>
    array(0) {
    }
  }
}

    */
?>