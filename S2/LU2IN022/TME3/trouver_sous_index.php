<?php
function trouver_sous_index ($t, $index)
{
    foreach ($t as $v) {
        if (isset($v[$index])) {
            return $v[$index];
        }
    }
    return array();
}
?>