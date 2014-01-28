(function ($) {
// JavaScript Document
$(document).ready(function() {
  // record the fact that they started watching the video
  jwplayer().onPlay(function() {
    // only track the first time play is pressed
    if (!Drupal.settings.user_progress.pressed_play) {
      var params = 'data1=1&data2=start&upregid='+ Drupal.settings.user_progress.upregid;
      Drupal.user_progress.ajax_call('set', 'value', params);
      // set true so that this can't happen again for this transaction
      Drupal.settings.user_progress.pressed_play = true;
    }
  });
  // flag that the user finished watching the video
  jwplayer().onComplete(function() {
    var params = 'data1=100&data2=complete&upregid='+ Drupal.settings.user_progress.upregid;
    Drupal.user_progress.ajax_call('set', 'value', params);
  });
  // Determine if the user jumped ahead of back in the video
  jwplayer().onSeek(function(event) {
    // round new and old positions to be whole numbers
    var offset = Math.round(event.offset);
    var position = Math.round(event.position);
    // calculate direction of the seek
    var pos = offset - position;
    var direction = '';
    // skip ahead
    if (pos > 0) {
      direction = 'forward';
    }
    // go back
    else {
      direction = 'back';
    }
    var params = 'data1='+ position +'&data2='+ direction +'&data3='+ offset +'&upregid='+ Drupal.settings.user_progress.upregid;
    Drupal.user_progress.ajax_call('set', 'value', params);
  });
  // monitor and report the entire process
  // this is an example of how to flood your database with meaningless data as this is the % left they have to watch of the video
  /* jwplayer().onTime(function(event) {
    var length = event.duration;
    var current = event.position;
    var params = 'value='+ Math.round(current/length * 100) +'&data=stamp&upregid='+ Drupal.settings.user_progress.upregid;
    Drupal.user_progress.ajax_call('set', 'value', params);
  });
  */
});
})(jQuery);