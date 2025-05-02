<?php
/// [1]: nom de la balise [2]: son contenu
define('RE_DTD_ELEMENT', "@<!ELEMENT\s+([\w:-]+)\s*([^>]*)\s*>@");
/// [1]: nom de la balise [2]: ses attributs
define('RE_DTD_ATTLIST', "@<!ATTLIST\s+([\w:-]+)\s*([^>]*)\s*>@");
/// [1]: nom de l'attribut [2]: son type [3]: son mode
define('RE_DTD_ATTRIBUTE', "@([\w:-]+)\s*(.*?)\s*#(\w+)@");
?>