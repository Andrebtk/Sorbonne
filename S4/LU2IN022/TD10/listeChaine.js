function listeChaine(data, sep){
    tab = data.split(sep);
    var ul = document.createElement('ul');
    for(var elem in tab){
        var li = ul.appendChild(document.createElement('li'));
        li.appendChild(document.createTextNode(tab[elem]));
    }

    return ul;
}