// JavaScript Document
(function ($) {
  // look for iframes on consumers we know about
  Drupal.behaviors.iframeProviderApply = {
  attach: function (context, settings) {
    $('iframe.entity_iframe').each(function(){
      var providers = Drupal.settings.entity_iframe.providers;
      var test = window.location.href;
      for (var i in providers){
        if (providers.hasOwnProperty(i)) {
          if (test.indexOf(providers[i]) != -1) {
            var url = $(this).attr('src'), idx = url.indexOf("#");
            var part = url.indexOf("?") != -1 ? "&" : "?";
            var hash = idx != -1 ? url.substring(idx) : "";
            url = idx != -1 ? url.substring(0, idx) : url;
            $(this).attr('src', url + part + 'entity_iframe=' + i + '/' + $(this).attr('id') + hash);
            return false;
          }
        }
      }
    });
    }
  };
  $(document).ready(function(){
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
      $('#' + iframeid + ':not(.entity_iframe_no_resize)').animate({
        height: frameheight,
      }, 300);
    });
  });
})(jQuery);