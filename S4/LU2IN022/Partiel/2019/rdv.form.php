<?php 
    include "mails.php";

    function rdv_form($list) {
        $res = "<form method='post' action='' ><fieldset>";
        $res .= "<ul>";
        foreach($list as $k=>$value){
            $res .= "<li><input type='checkbox' name='qui[]' id='checkbox' value='$k'>"
                . "<label for='checkbox'>". htmlspecialchars($value) . "</label></li>";
        }
        $res .= "</ul>";
        $res .= "<input type='submit'>";
        return $res . "</fieldset></form>";
    }

    

    
    //echo rdv_form($mails);

?>