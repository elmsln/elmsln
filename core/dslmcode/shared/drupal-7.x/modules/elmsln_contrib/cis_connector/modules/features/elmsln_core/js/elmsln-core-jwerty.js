(function ($) {
  // apply jwerty keys to listen for
  $(document).ready(function(){
    // voice based video controls... within reason
    Drupal.voicecommander.controlVideo = function(phrase) {
      if (phrase.indexOf('play') !== -1) {
        // @todo something like this...
        /*$( 'iframe[src*="youtube.com"]' ).each( function( i, el ) {
          var youtube_command = window.JSON.stringify( { event: 'command', func: 'playVideo' } );
          console.log(i);
          console.log(el);
          i.postMessage( youtube_command, 'https://www.youtube.com' );
        });*/
      }
      // travel to the top of the screen
      else if (phrase.indexOf('pause') !== -1) {
        /*$( 'iframe[src*="youtube.com"]' ).each( function( i, el ) {
          var youtube_command = window.JSON.stringify( { event: 'command', func: 'pauseVideo' } );
          console.log(i);
          console.log(el);
          i.postMessage( youtube_command, 'https://www.youtube.com' );
        });*/
      }
    };
    jwerty.key('↓,↓', function () {
      var height = $(window).height();
      $('html, body').animate({
          scrollTop: $(window).scrollTop()+(height*0.75)
      }, 1000);
      return false;
    });
    jwerty.key('↑,↑', function () {
      var height = $(window).height();
      $('html, body').animate({
        scrollTop: $(window).scrollTop()-(height*0.75)
      }, 1000);
      return false;
    });
    // network
    jwerty.key('n', function () {
      $('.apps-icon').click();
    });
    // user
    jwerty.key('u', function () {
      $('.etb-nav_item_service_btn.etb-icon.user-icon').click();
    });
  });
})(jQuery);