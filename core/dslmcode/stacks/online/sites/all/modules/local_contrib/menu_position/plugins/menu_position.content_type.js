(function ($) {

/**
 * Provide the summary information for the content type plugin's vertical tab.
 */
Drupal.behaviors.menuPositionContentTypeSettingsSummary = {
  attach: function (context) {
    $('fieldset#edit-content-type', context).drupalSetSummary(function (context) {
      var vals = [];
      $('input[type="checkbox"]:checked', context).each(function () {
        vals.push($.trim($(this).next('label').text()));
      });
      if (!vals.length) {
        vals.push(Drupal.t('Any content type'));
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);
