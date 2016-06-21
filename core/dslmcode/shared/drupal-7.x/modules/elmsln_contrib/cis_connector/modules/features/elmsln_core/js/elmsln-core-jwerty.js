(function ($) {
  // apply jwerty keys to listen for
  $(document).ready(function(){
    // voice based video controls... within reason
    Drupal.voicecommanderControlVideo = function(phrase) {
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
      if (!$(document.activeElement).is(":focus")) {
        var height = $(window).height();
        $('html, body').animate({
            scrollTop: $(window).scrollTop()+(height*0.75)
        }, 1000);
      }
      return false;
    });
    jwerty.key('↑,↑', function () {
      if (!$(document.activeElement).is(":focus")) {
        var height = $(window).height();
        $('html, body').animate({
          scrollTop: $(window).scrollTop()-(height*0.75)
        }, 1000);
        return false;
      }
    });
    // network
    jwerty.key('alt+shift+n', function () {
      $('.elmsln-network-button').focus().click();
    });
    // network
    jwerty.key('alt+shift+u', function () {
      $('.elmsln-user-button').focus().click();
    });
    // edit
    jwerty.key('alt+shift+e', function () {
      if (!$(document.activeElement).is(":focus") && $('.elmsln-edit-button').attr('href') && window.location != $('.elmsln-edit-button').attr('href')) {
        window.location = $('.elmsln-edit-button').attr('href');
      }
    });
    // share
    jwerty.key('alt+shift+s', function () {
      $('.elmsln-share-button').focus().click();
    });
    // accessibility menu
    jwerty.key('alt+shift+a', function () {
      $('.elmsln-accessibility-button').focus().click();
    });
    // more
    jwerty.key('alt+shift+m', function () {
      $('.elmsln-more-button').focus().click();
    });
    // add
    jwerty.key('alt+shift+d', function () {
      $('.add-menu-drop').focus().click();
    });
  });
})(jQuery);