<?php 
    include "../TME2/debut_html.php";
    
    function webmail_form($title, $name, $mdp) {
        $name = htmlspecialchars($name);
        $mdp = htmlspecialchars($mdp);
        return debut_html($title)
            . "<body>"
            . "<h1>" . $title . "</h1>"
            . "<form action='' method='post'><fieldset>"
            . "<label for='nom'>Nom</label>"
            . "<input type='text' name='nom' id='nom' value='$name' />"
            . "<label for='mdp'>Password</label>"
            . "<input type='password' id='mdp' name='mdp' value='$mdp' />"
            . "<input type='submit'>"
            ."</fieldset></form>"
            . "</body></html>";
    }   

?>