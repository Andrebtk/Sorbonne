function libmus_historique() {
    var date_ins, type_ins, search_ins;
    var c = document.cookie.split(";").forEach(function(e){
        var nom = e.split('=')[0];
        var val = e.split('=')[1];

        if(nom == "recherche") {
            search_ins = val;
        }
        else if (nom == "type"){
            type_ins = val;
        } 
        else if (nom == "date_heure"){
            date_ins = val;
        }

    });
    var txt = "["+date_ins+"]"+" Recherche d\'un " + type_ins + " : " + search_ins;
    var li = document.createElement('li');

    li.appendChild(document.createTextNode(txt));

    document.getElementById('hist-liste').appendChild(li);

}