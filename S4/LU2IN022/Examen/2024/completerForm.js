function completerForm(form, qs){
    ajax('reponse_ajax.php', qs,function(xhr){
        var l = document.createElement('div');
        l.innerHTML = xhr.responseText;
        form.appendChild(l);
    },'POST');
}