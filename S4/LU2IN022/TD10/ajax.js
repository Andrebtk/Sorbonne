/// Fonction d'envoi de requetes asynchrones:
/// url: ressource sur le serveur courant, avec query-string eventuelle;
/// flux: flux d'entree en cas de methode POST;
/// method: methode HTTP (GET par defaut);
/// rappel: fonction a appliquer sur l'objet Ajax lorsque le serveur a fini de répondre,
/// peut aussi etre un tableau de 5 fonctions, une par étape.
/// Retourne True si requête envoyée, False sinon
function ajax(url, flux, rappel, method) {
    var r = window.XMLHttpRequest ? new XMLHttpRequest() :
      (window.ActiveXObject ?  new ActiveXObject("Microsoft.XMLHTTP") : '');
    if (!r) return false;
    if (rappel) {
	if (!rappel.isArray) rappel = [,,,,rappel];
	r.onreadystatechange = function () {
	    if (typeof(rappel[r.readyState]) == 'function') rappel[r.readyState](r);}
    }
    r.open(method ? method : 'GET', url, true);
    if (flux)
	r.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    r.send(flux);
    return true;
}