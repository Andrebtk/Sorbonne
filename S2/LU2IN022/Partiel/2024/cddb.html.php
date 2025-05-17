<?php 


    function cddb_html($titre, $corp='', $charset='utf-8', $lang='fr') {
        return
        "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML Basic 1.1//EN'
            'http://www.w3.org/TR/xhtml-basic/xhtml-basic11.dtd'>\n" .
        "<html xmlns='http://www.w3.org/1999/xhtml' lang='$lang'>\n" .
        "<head>\n" .
        "<meta http-equiv='Content-Type' content='text/html;charset=$charset' />\n" .
        "<title>" . 
        $titre .
        "</title>\n" .
        "</head><body><h1>$titre</h1>\n" .
        $corp . "</body></html>";
        ;
    }

?>