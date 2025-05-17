<?php
include '../../TME3/tableau_en_select.php';
include '../../TD3/html_form.php';

function choisir_style ($urls, $media, $choix=array())
{
    $corps = '';
    $urls = array($urls);
    foreach($media as $medium) {
        $corps .= tableau_en_select($urls, $medium, isset($choix[$medium]) ? $choix[$medium] : 0);
    }
    return html_form($corps . "<input type='submit' />", 'post');
}
/*// Test
echo choisir_style(array('0.css', '1.css', '2.css'),
                   array('print' , 'handheld', 'screen'),
                   array('print' => 2, 'handheld' => 0, 'screen' => 1)
);
//*/
?>
