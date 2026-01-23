<?php 
    include '../TD3/saisie_fiable.php';
    include '../TD2/re_heure.php';
    include '../TD2/re_jour.php';

    $jour = saisie_fiable($_POST, 'date', RE_JOUR);
    $h_debut = saisie_fiable($_POST, 'h_debut', RE_HEURE);
    $h_fin = saisie_fiable($_POST, 'h_fin', RE_HEURE);

    $file = empty($_FILES['ics']) ? '' :
      (empty($_FILES['ics']['tmp_name']) ? false : $_FILES['ics']['tmp_name']);

    if( /*$jour OR $h_debut OR $h_fin OR */ !$file){

        ?>
<form action='' method='post' >
    <label for='ics'>ICS: </label>
    <input type='file' name='ics' id='ics' accept='text/calendar' /><br>

    <label for='date'>Date: </label>
    <input type='text' name='date' id='date' /><br>

    <label for='h_debut'>Heure debut: </label>
    <input type='text' name='h_debut' id='h_debut' /><br>

    <label for='h_fin'>Heure Fin: </label>
    <input type='text' name='h_fin' id='h_fin' /><br>

    <input type='submit'/>
</form>

    <?php

    }else{

    }


    
?>