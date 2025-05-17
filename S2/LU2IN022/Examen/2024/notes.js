document.querySelectorAll("td").forEach(function(e) {
    if(e.innerHTML < 10) {
        e.style.color = 'red';
    } else if ((e.innerHTML > 10) && (e.innerHTML <= 15)) {
        e.style.color = 'orange';
    }else if (e.innerHTML>15){
        e.style.color = 'green';
    }
})