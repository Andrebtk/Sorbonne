<?php

    function bibu_form($str) {
        return "<form action='' method='get'>"
            . "<fieldset>"
            . "<label for='atuer'>Auteur</label>"
            . "<input type='text' id='auteur' name='auteur' value='$str' />"
            ."</fieldset></form>";
    }   

?>