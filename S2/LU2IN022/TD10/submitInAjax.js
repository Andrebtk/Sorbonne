function submitInAjax(node) {
    var saisie = 0;
    var qs = new Array();

    for(var k in node.elements){
        var elem = node.elements[k];
        var name = elem.name;
        var val = elem.value;
        if(elem.checked != false) {
            saisie++;
            qs[saisie] = name + ":" + val;
        }
    }


    if(saisie==0) {
        alert();
        return false;
    }
    else {
        var final_qs = qs.join('&');
        if(node.method === "post"){
            if(ajax(node.action, final_qs, insereAjax, node.method)){
                return false;
            }
        }
        else {
            if(ajax(node.action + "?" + final_qs, '', insereAjax, node.method)){
                return false;
            }
        }
        
    }
}