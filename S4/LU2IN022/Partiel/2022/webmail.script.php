<?php 
    include "webmail.re.php";
    include "webmail.auth.php";
    include "webmail.form.php";
    include "webmail.pop.php";
    

    var_dump($_COOKIE);
    $name = isset($_POST['nom'])? $_POST['nom']: '';
    $password = isset($_POST['mdp'])? $_POST['mdp']: '';


    $titre='';
    if ($name == '' AND $password == '') $titre = 'Webmail';
    $err=false;
    $port = false;
    
    if (preg_match(RE_USR, $name) ){

        if ( preg_match(RE_MDP, $password) ) {
            $port = webmail_auth($name, $mdp);
            if($port != false) {
                webmail_pop($name,$password,$port);
            } else {
                $err = true;
                $titre .= "webmail_auth";
            }
        } else {
            $err = true;
            $titre .= "PASSWORD";
        }
       
    } else {
       
       $err = true;
       $titre .= "USER";

    }
    if ($err) {
        header("HTTP/1.1 403");
    }
    if (!$port) {
        setcookie("Name", $$name, time()+(7*24*60*60));  
        echo webmail_form($titre, $name, $password);
    }
   
?>
