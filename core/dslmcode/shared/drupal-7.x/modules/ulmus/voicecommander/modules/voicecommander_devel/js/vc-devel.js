/**
 * @file
 *
 * Debugging console output on all matches.
 */

(function ($) {
  // all result matches will print debug info
  annyang.addCallback('resultMatch', function(userSaid, commandText, phrases) {
    console.log('command that matched: ' + commandText);
    console.log('user said: ' + userSaid);
    console.log('phrases that matched:');
    console.log(phrases);
  });
  // no match
  annyang.addCallback('resultNoMatch', function(phrases) {
    console.log('no matches but results were:');
    console.log(phrases);
  });
})(jQuery);
