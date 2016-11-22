(function ($) {
  $(document).ready(function(){
    var useItOnce = true;
    // self discover
    Drupal.keys = {};
    $('[data-jwerty-key]').each(function(){
      Drupal.keys[$(this).attr('data-jwerty-key')] = this;
      jwerty.key('alt+shift+' + $(this).attr('data-jwerty-key'), function (event, selector) {
        var key = selector.replace('alt+shift+', '');
        if ($(Drupal.keys[key]).attr('href') == '' || $(Drupal.keys[key]).attr('href') == undefined || $(Drupal.keys[key]).attr('href').substring(0,1) == '#') {
          $(Drupal.keys[key]).focus().click();
        }
        else {
          window.location = $(Drupal.keys[key]).attr('href');
        }
      });
    });
    // visualize what CAN be pressed
    $(document).keydown(function (event) {
      if (event.shiftKey && event.altKey && useItOnce) {
        $('[data-jwerty-key]').each(function(){
          $(this).prepend('<span class="jwerty-key">' + $(this).attr('data-jwerty-key') + '</span>');
        }).addClass('jwerty-key-outline').css('opacity', 1);
        useItOnce = false;
      }
    });
    // disable the visual
    $(document).keyup(function (event) {
      if (event.shiftKey || event.altKey) {
        $('span.jwerty-key').remove();
        $('[data-jwerty-key]').removeClass('jwerty-key-outline').css('opacity', '');
        useItOnce = true;
      }
    });
  });
})(jQuery);