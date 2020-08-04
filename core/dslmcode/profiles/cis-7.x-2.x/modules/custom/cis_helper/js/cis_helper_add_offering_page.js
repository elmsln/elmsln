/**
 * @file
 * Simple URL builder based on inputs
 */
(function ($) {
    $(document).ready(function(){
        setTimeout(function() {
            fullUrlBuilder();
            document.getElementById('edit-courses').addEventListener('change', function(e){
                fullUrlBuilder();
            });
            document.getElementById('edit-access-string').addEventListener('input', function(e){
                fullUrlBuilder();
            });
        }, 5000);
    });
})

function fullUrlBuilder() {
    var fullUrl = Drupal.settings.elmslnCore.url.replace('cis-add-offering', 'course-redirect/');
    fullUrl += document.getElementById('edit-courses').value + '/';
    fullUrl += document.getElementById('edit-access-string').value;
    if (!document.getElementById('custom-div')) {
        var div = document.createElement('div');
        div.setAttribute('id', 'custom-div');
        document.getElementById('cis-helper-add-offering-page').appendChild(div);
    }
    console.log(fullUrl);
    document.getElementById('custom-div').innerHTML = '<strong>Access URL:</strong> ' + fullUrl;
}