<?php
/// Presenter un tableau sous forme de liste, recursivement.
/// La liste est UL ou OL selon le 2e argument.
/// Contrairement aux apparences,
/// les LI ouvrants précèdent les fermants au final.
function tableau_en_liste ($data, $type='ul')
{
    if (!is_array($data))
        return $data;
    if (count($data) == 1)
        return array_shift($data);
   foreach($data as $k => $v) $data[$k] = tableau_en_liste($v, $type);
   return "<$type><li>" . join("</li>\n\t<li>", $data) . "</li></$type>\n";
}
/*// Test
include '../../TM/3/destinations.php';
echo tableau_en_liste($destinations);
//*/
?>