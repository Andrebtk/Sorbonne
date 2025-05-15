<?php

    if( empty($_FILES['ics1']['tmp_name']) OR empty($_FILES['ics2']['tmp_name'])) {
        ?>
            <DOCTYPE html>
            <body>
                <form action='' method='post' enctype='multipart/form-data'>
                    <label for='ics1'>ICS1</label>
                    <input type='file' name='ics1' id='ics1' accept='text/calendar' />
                    
                    <label for='ics2'>ICS2</label>
                    <input type='file' name='ics2' id='ics2' accept='text/calendar' /> 

                    <input type='submit'/>
                </form>
            </body>

        <?php
    }
    else {
        include 'envoi_ics.php';
        include 'fusionne_ics.php';
        $t = fusionne_ics($_FILES['ics1']['tmp_name'], $_FILES['ics2']['tmp_name']);
        envoie_ics($t, "res");
    }

?>