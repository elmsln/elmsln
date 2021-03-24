(function ($) {

Drupal.behaviors.linkcheckerFieldsetSummaries = {
  attach: function (context) {
    // Provide the vertical tab summaries.
    $('fieldset#edit-linkchecker', context).drupalSetSummary(function(context) {
      var vals = [];
      $('input:checked', context).next('label').each(function() {
        vals.push(Drupal.checkPlain($(this).text()));
      });
      if (!vals.length) {
        return Drupal.t('Disabled');
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);
