var time_out;


function merci(node) {
    document.getElementById("non").style = 'opacity:.9';
    clearTimeout(time_out);
    var t = document.createTextNode("Merci d'avoir dit: " + node.firstChild.data);
    document.getElementById("titre").appendChild(t);

    ajax("inaccessible.php","",insereAjax,"GET");
}


function bouger(node) {
    var x = Math.ceil((Math.random() *  window.innerHeight)-75);
    var y = Math.ceil((Math.random() * window.innerWidth)-75);
    
    node.style.opacity /= 2;
    node.style.top = x+"px";
    node.style.left = y+"px";
    clearTimeout(time_out);

    ajax("inaccessible.php?left:"+ node.style.top+"&top:"+ node.style.top,"","","GET");

}

function reveille(){
    time_out = setTimeout(() => {
        var t=document.getElementById("titre")
        t.style.fontSize = (parseFloat(t.style.fontSize)*3/2) + "em";
        reveille()
    }, "5000");       
}


// Deux fonctions vues en TD
function insereAjax(xhr) {
    var c = (xhr.status >= 300) ?
        document.createTextNode('Erreur ' + xhr.status + xhr.responseText):
        listeChaine(xhr.responseText, "\n");
    document.body.appendChild(c);
}

function listeChaine(choix, sep) {
    var u = document.createElement('ul');
    choix.split(sep).forEach(function(i) {
        if (i) {
            var l = document.createElement('li');
            l.appendChild(document.createTextNode(i));
            u.appendChild(l);
        }
    })
    return u;
}
