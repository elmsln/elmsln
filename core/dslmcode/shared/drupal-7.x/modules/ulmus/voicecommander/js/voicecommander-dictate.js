/**
 * @file
 *
 * Custom module js file.
 */

(function ($) {
  Drupal.voicecommander.dictate = function(wildcard) {
    $(":focus").html($(":focus").html() + wildcard);
  };
  annyang.addCallback('resultMatch', function(userSaid, commandText, phrases) {
    console.log(userSaid); // sample output: 'hello'
    console.log(commandText); // sample output: 'hello (there)'
    console.log(phrases); // sample output: ['hello', 'halo', 'yellow', 'polo', 'hello kitty']
  });
})(jQuery);
