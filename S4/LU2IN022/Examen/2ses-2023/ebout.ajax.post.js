function ebout_ajax_post(categorie) {
    ajax('ebout.php','id_categorie='+categorie,ebout_xhr_post,'POST')
}


function ebout_xhr_post(xhr) {
    document.querySelector("div[id=liste]").innerHTML = xhr.responseText;
}