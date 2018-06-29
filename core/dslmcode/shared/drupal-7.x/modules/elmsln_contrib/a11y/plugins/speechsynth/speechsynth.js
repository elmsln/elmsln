(function ($) {
  $(document).ready(function(){
    $('#a11y_speechsynth_checkbox').click(function(){
      if (this.checked) {
        Drupal.a11y.speechSynth(this.checked);
      }
      else {
        window.speechSynthesis.cancel();
      }
    });
    if (typeof window.speechSynthesis !== "undefined") {
      window.speechSynthesis.cancel();
    }
    // @todo make a setting for automatically going to the next page
    // to basically keep reading along with you
    // @todo ability to underline word it is saying as well as scroll the page for it to be in view
    // test for cookie being set
    //if ($.cookie('a11y_speechsynth') == 'true') {
    //  $('#a11y_speechsynth_checkbox').click();
    //}
  });
  // speechSynth functionality
  Drupal.a11y.speechSynth = function(speechSynth){
    var text = $(Drupal.settings.a11y.speechSynthSelector).text();
    Drupal.a11y.say(text);
    //$.cookie('a11y_speechsynth', speechSynth, { path: '/', domain: Drupal.settings.a11y.domain });
  };
  // say something to the user if asked
  Drupal.a11y.say = function(text, pitch, rate) {
    // talk to me
    if (typeof window.speechSynthesis !== "undefined") {
      Drupal.settings.a11y.synth = window.speechSynthesis;
      Drupal.settings.a11y.voices = Drupal.settings.a11y.synth.getVoices();
      Drupal.settings.a11y.utter = new SpeechSynthesisUtterance(text);
      // nothing crazy so we can understand our robot
      if (typeof pitch === 'undefined') {
        Drupal.settings.a11y.utter.pitch = 1;
      }
      else {
        Drupal.settings.a11y.utter.pitch = pitch;
      }
      if (typeof rate === 'undefined') {
        Drupal.settings.a11y.utter.rate = 1;
      }
      else {
        Drupal.settings.a11y.utter.rate = rate;
      }
      Drupal.settings.a11y.utter.lang = 'en-US';
      Drupal.settings.a11y.utter.voice = Drupal.settings.a11y.defaultVoice;
      // THOU SPEAKITH
      Drupal.settings.a11y.synth.speak(Drupal.settings.a11y.utter);
    }
  };
})(jQuery);
