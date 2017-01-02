(function ($) {
  // apply jwerty keys to listen for
  $(document).ready(function(){
    // say where they are contextually
    Drupal.voicecommanderWhereAmI = function(phrase) {
      var context = Drupal.settings.elmslnCore;
      var spokenContext = 'You are logged in as ' + context.uname + ' which is a ' + context.role + ' role, experiencing ' +  context.course + ', ' + context.section + ' section. You are working with the ' + context.name + ', viewing a page called ' + context.title + '.';
      Drupal.voicecommander.say(spokenContext);
    };
    Drupal.voicecommanderGoToELMSLN = function(phrase) {
      window.location.href = Drupal.settings.voiceCommander.commands[phrase].data;
    };
    // voice based video controls... within reason
    Drupal.voicecommanderControlVideo = function(phrase) {
      if (phrase.indexOf('play') !== -1) {
        // @todo something like this...
        /*$( 'iframe[src*="youtube.com"]' ).each( function( i, el ) {
          var youtube_command = window.JSON.stringify( { event: 'command', func: 'playVideo' } );
          i.postMessage( youtube_command, 'https://www.youtube.com' );
        });*/
      }
      // travel to the top of the screen
      else if (phrase.indexOf('pause') !== -1) {
        /*$( 'iframe[src*="youtube.com"]' ).each( function( i, el ) {
          var youtube_command = window.JSON.stringify( { event: 'command', func: 'pauseVideo' } );
          i.postMessage( youtube_command, 'https://www.youtube.com' );
        });*/
      }
    };
    // voice based video controls... within reason
    Drupal.voicecommanderHal9000 = function(phrase) {
      if (phrase == 'new grounds') {
        Drupal.voicecommander.say('All your base, base, base, all your base, are belong to us.', 0.1, .6);
      }
      else {
        Drupal.voicecommander.say('I\'m sorry Dave. I\'m afraid I can\'t do that.', 0.1, .6);
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
  });
})(jQuery);