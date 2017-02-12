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
    // word count
    Drupal.voicecommanderWordCount = function(phrase) {
      total_words=$('article').text().split(/[\s\.\?]+/).length;
      Drupal.voicecommander.say('There are ' + total_words + ' total words in this document.');
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
    // easter eggs
    Drupal.voicecommanderMakeCoffee = function(phrase) {
      Drupal.voicecommander.say('Why don\'t you get me a coffee! I do all the hard work anyway. I\'ll have a venti americano with six shots of expresso. It was a rough night last night processing all those rosters.');
      window.location.href = 'https://starbucks.com';
    };
    Drupal.voicecommanderAllYourBase = function(phrase) {
      Drupal.voicecommander.say('are belong to us');
    };
    // creepy voice
    Drupal.voicecommanderHal9000 = function(phrase) {
      Drupal.voicecommander.say('I\'m sorry Dave. I\'m afraid I can\'t do that.', 0.1, .6);
    };
    // creepy voice
    Drupal.voicecommanderThankYou = function(phrase) {
      Drupal.voicecommander.say('No, thank you for asking.');
    };
    // triggerclose
    Drupal.voicecommanderCloseMenus = function(phrase) {
      $('[data-voicecommand="close (menu)"],[data-voicecommand="close"]').click();
    };
  });
})(jQuery);