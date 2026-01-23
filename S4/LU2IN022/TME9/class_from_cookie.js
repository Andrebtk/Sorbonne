function class_from_cookie() {
    var c = document.cookie;
    c.split("; ").forEach(function(x) {
        var dom = document.getElementById(x.split("=")[0])
        dom.class=x.split("=")[1]

        document.cookie = x.split("=")[0] + "= ;expires=Thu, 01 Jan 1970 00:00:00 UTC";
        console.log(dom);
    })
}