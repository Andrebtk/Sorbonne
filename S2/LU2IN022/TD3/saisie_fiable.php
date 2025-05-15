<?php
/// Teste si le tableau $t contient l'index $index
/// et alors si la valeur liée à cet index est conforme à la regexp $re.
/// Si l'élement est absent retourne 1
/// Sinon si $re est absent ou si la valeur est conforme à $re, retourne 0
/// Autrement retourne -1
function saisie_fiable($t, $index, $re='')
{
    if (!isset($t[$index])) return 1;
    if (!$re OR (is_string($t[$index]) AND preg_match($re, $t[$index])))
        return 0;
    return -1;
}
?>