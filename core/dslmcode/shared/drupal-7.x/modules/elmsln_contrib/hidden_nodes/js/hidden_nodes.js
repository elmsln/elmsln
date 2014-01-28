(function ($) {

Drupal.behaviors.hiddenNodeFieldsetSummaries = {
  attach: function (context) {
    $('fieldset#edit-hidden-nodes', context).drupalSetSummary(function (context) {
      var hid = $('input', context).is(':checked');

      return hid ?
        Drupal.t('Hidden') :
        Drupal.t('Normal (not hidden)'); 
    });
  }
};

})(jQuery); 
