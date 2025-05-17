function libmus_xhr(xhr) {
    if(xhr.readyState != 4)
        return ;

    if(xhr.status!=200){
        alert('Erreur code pas 200');
        return;
    } 

    var resp = xhr.responseText;
    var nom_alb_art = resp.split('#')[0];
    var type_recherche = resp.split('#')[1];

    document.getElementsByClassName('artiste');
}