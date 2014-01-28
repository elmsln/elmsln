// JavaScript Document
(function($) {
  $(document).ready(function(){
    // look for iframes on consumers we know about
    $('iframe.entity_iframe').each(function(){
      var providers = Drupal.settings.entity_iframe.providers;
      var test = $(this).attr('src');
      for (var i in providers){
        if (providers.hasOwnProperty(i)) {
          if (test.indexOf(providers[i]) != -1) {
            $(this).attr('src', $(this).attr('src') + '?entity_iframe=' + i + '/' + $(this).attr('id'));
          }
        }
      }
    });
    // height resize handler
    $('#entity_iframe_response').click(function(){
      var data = $(this).val().split('#');
      iframeid= data[0];
      data = data[1].split('&');
      for (var i in data){
        var parts = data[i].split('=');
        if (parts[0] == 'h') {
          var frameheight = parts[1];
        }
      }
      $('#' + iframeid).animate({
        height: frameheight,
      }, 300);
    });
  });
})(jQuery);