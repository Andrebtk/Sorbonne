function insereAjax(req) {
    var rep = req.responseText;
    var sta = req.status;

    if(sta<300) {
        document.body.appendChild(listeChaine(rep, "\n"));
    } 
    else {
        document.body.appendChild(document.createTextNode("ERREUR: "+sta+req));
    }

    
}