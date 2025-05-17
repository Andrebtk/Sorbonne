function libmus_ajax(form) {
    var search = form.elements['search'];
    var type = form.elements['type'];
    
    if(search == ''){
        alert('Erreur recherche vide');
        return false;
    }

    var qs = "search:"+search+"&type:"+type;
    return !ajax(form.action,qs,libmus_xhr,'POST');

}