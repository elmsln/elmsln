(function ($) {

/**
 * Provide the summary information for the pages plugin's vertical tab.
 */
Drupal.behaviors.menuPositionPagesSettingsSummary = {
  attach: function (context) {
    $('fieldset#edit-pages', context).drupalSetSummary(function (context) {
      if (!$('textarea[name="pages"]', context).val()) {
        return Drupal.t('Any page');
      }
      else {
        return Drupal.t('Restricted to certain pages');
      }
    });
  }
};

})(jQuery);
