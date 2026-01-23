var time_out;


function merci(node) {
    document.getElementById("non").style = 'opacity:.9';
    clearTimeout(time_out);
    var t = document.createTextNode("Merci d'avoir dit: " + node.firstChild.data);
    document.getElementById("titre").appendChild(t);
}


function bouger(node) {
    var x = Math.ceil((Math.random() *  window.innerHeight)-75);
    var y = Math.ceil((Math.random() * window.innerWidth)-75);
    
    node.style.opacity /= 2;
    node.style.top = x+"px";
    node.style.left = y+"px";
    clearTimeout(time_out);
}



function reveille(){
    
    time_out = setTimeout(() => {
        var t=document.getElementById("titre")
        t.style.fontSize = (parseFloat(t.style.fontSize)*3/2) + "em";
        reveille()
    }, "5000");
    
        
}