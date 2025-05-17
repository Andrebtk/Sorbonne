function libmus_event() {
    document.querySelectorAll('.descr').forEach(function(e) {
        e.style.display = 'none';
        e.addEventListener('click', function() {
            if(e.style.display == 'none'){
                e.style.display = 'block';
            } else if (e.style.display == 'block'){
                e.style.display = 'none'
                
            }
        })
    })
}