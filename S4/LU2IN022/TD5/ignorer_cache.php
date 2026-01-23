<?php
    /// Si pas d'Expire ou Expire pas dans le futur, retourner True
    function ignorer_cache ($headers) {
        if (!isset($headers['Expires'])) return true;
        return (strtotime($headers['Expires'][0]) < time()) ;
    }
?>