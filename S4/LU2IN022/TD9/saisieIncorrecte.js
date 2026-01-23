function saisieIncorrecte(node, re) {
    if(re==='') return node;

    if(re.test(node.value)){
        node.style.border_color = 'red';
        node.style.border_style = 'dashed';
        node.style.border_width = '2px';
        return node;
    }
    else {
        node.style.border_color = 'black';
        node.style.border_style = 'solid';
        node.style.border_width = '1px';
        return false;
    }
}