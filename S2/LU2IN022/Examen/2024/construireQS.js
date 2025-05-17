function construireQS(form) {
    var qs = ''
    var elems = form.elements;
    for (i in elems) {
        var e = elems[i];
        if( (e.name == 'cours') || (e.name == 'evaluation')){
            qs = qs + e.name +'='+e.value;
        }
    }

    return qs;
}