<?php

include "sax_notes.php";

function phraser($source, $instance)
{
	if (!$f = @fopen($source, "r"))
    	return("Impossible de lire '$source'");
    $sax = xml_parser_create();
    xml_set_element_handler($sax,
                            array($instance, 'ouvrante'),
                            array($instance, 'fermante'));
    xml_set_character_data_handler($sax, array($instance, 'texte'));
    xml_parser_set_option($sax, XML_OPTION_CASE_FOLDING, false);
    while ($data = fread($f, 8192)) {
        if (!xml_parse($sax, $data, feof($f))) {
            $data = "Erreur XML :" .
                  xml_error_string(xml_get_error_code($sax)) .
                  " ligne " .
                  xml_get_current_line_number($sax);
            break;
        }
    }
    fclose($f);
    $res = $instance->retour($data);
    xml_parser_free($sax);
    return $res;
}
 
//var_dump(phraser('notes.xml', new sax_notes));

/*

array(3) {
  ["LU2IN001"]=>
  array(3) {
    ["nom"]=>
    string(13) "Algorithmique"
    ["partiel"]=>
    array(2) {
      ["coefficient"]=>
      string(1) "2"
      ["notes"]=>
      array(9) {
        [21210001]=>
        string(2) "12"
        [21210002]=>
        string(2) "15"
        [21210003]=>
        string(2) "10"
        [21210004]=>
        string(1) "8"
        [21210011]=>
        string(2) "14"
        [21210012]=>
        string(2) "16"
        [21210013]=>
        string(2) "12"
        [21210014]=>
        string(2) "10"
        [21210015]=>
        string(2) "14"
      }
    }
    ["final"]=>
    array(2) {
      ["coefficient"]=>
      string(1) "3"
      ["notes"]=>
      array(7) {
        [21210001]=>
        string(2) "14"
        [21210002]=>
        string(2) "16"
        [21210003]=>
        string(2) "12"
        [21210011]=>
        string(2) "16"
        [21210012]=>
        string(2) "18"
        [21210014]=>
        string(2) "14"
        [21210015]=>
        string(2) "12"
      }
    }
  }
  ["LU2IN002"]=>
  array(4) {
    ["nom"]=>
    string(16) "Base de données"
    ["partiel"]=>
    array(2) {
      ["coefficient"]=>
      string(1) "2"
      ["notes"]=>
      array(8) {
        [21210001]=>
        string(2) "14"
        [21210002]=>
        string(2) "16"
        [21210003]=>
        string(2) "12"
        [21210004]=>
        string(2) "10"
        [21210011]=>
        string(2) "16"
        [21210012]=>
        string(2) "18"
        [21210013]=>
        string(2) "14"
        [21210016]=>
        string(2) "12"
      }
    }
    ["tp"]=>
    array(1) {
      ["notes"]=>
      array(8) {
        [21210001]=>
        string(2) "16"
        [21210002]=>
        string(2) "18"
        [21210003]=>
        string(2) "14"
        [21210005]=>
        string(2) "12"
        [21210011]=>
        string(2) "18"
        [21210012]=>
        string(2) "20"
        [21210015]=>
        string(2) "16"
        [21210016]=>
        string(2) "14"
      }
    }
    ["final"]=>
    array(2) {
      ["coefficient"]=>
      string(1) "5"
      ["notes"]=>
      array(6) {
        [21210001]=>
        string(1) "9"
        [21210002]=>
        string(2) "18"
        [21210003]=>
        string(2) "14"
        [21210011]=>
        string(2) "18"
        [21210012]=>
        string(2) "20"
        [21210015]=>
        string(2) "16"
      }
    }
  }
  ["LU2IN003"]=>
  array(2) {
    ["nom"]=>
    string(7) "Logique"
    ["final"]=>
    array(1) {
      ["notes"]=>
      array(10) {
        [21210001]=>
        string(2) "18"
        [21210002]=>
        string(2) "20"
        [21210003]=>
        string(2) "16"
        [21210004]=>
        string(2) "16"
        [21210005]=>
        string(2) "14"
        [21210006]=>
        string(2) "12"
        [21210007]=>
        string(2) "10"
        [21210008]=>
        string(1) "8"
        [21210009]=>
        string(1) "6"
        [21210010]=>
        string(1) "4"
      }
    }
  }
}

*/
?>
