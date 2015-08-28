// JavaScript Document
(function($) {
  $(document).ready(function(){
    var h = $(document).height();
    var url = window.location.href;
    $('body').append('<iframe id="entity_iframe_consumer_backdoor" src="' + Drupal.settings.entity_iframe.consumer[0] + '/entity-iframe-consumer.html?iframeid=' + Drupal.settings.entity_iframe.consumer[1] + '" width="1" height="1"/>');
    $('#entity_iframe_consumer_backdoor').attr('src', ($('#entity_iframe_consumer_backdoor').attr('src') + '#h=' + h + '&url=' + url));
  });
})(jQuery);
