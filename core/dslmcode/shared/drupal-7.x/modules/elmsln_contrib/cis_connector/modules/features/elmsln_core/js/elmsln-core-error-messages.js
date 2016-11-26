(function ($) {
  // apply jwerty keys to listen for
  $(document).ready(function(){
    Drupal.voicecommander.say('I\'m sorry Dave. I\'m afraid I can\'t do that.', 0.1, .6);
    setInterval(function(){ $('.error-page-hal9000').addClass('on'); }, 1000);
    setInterval(function(){ $('.error-page-hal9000').removeClass('on'); }, 2000);
  });
})(jQuery);