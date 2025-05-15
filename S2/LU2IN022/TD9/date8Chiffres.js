 function date8Chiffres() {
    var d = new Date();
    var a = d.getFullYear();
    var m = d.getMonth()+1;
    var j = d.getDate();
    /// ne pas fractionner cette expression:
    /// c'est la présence des "'" qui force "+" a etre une concatenation
    return a + ((m <= 9) ? '0' : '') + m + ((j <= 9) ? '0' : '') + j;
}