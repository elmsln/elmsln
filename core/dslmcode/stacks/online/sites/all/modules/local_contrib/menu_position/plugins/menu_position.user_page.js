(function ($) {

/**
 * Provide the summary information for the content type plugin's vertical tab.
 */
Drupal.behaviors.menuPositionUserPageSettingsSummary = {
  attach: function (context) {
    $('fieldset#edit-user-page', context).drupalSetSummary(function (context) {
      if (!$('input#edit-user-page-enable:checked').length) {
        return Drupal.t('Ignore user account page');
      }
      else {
        return Drupal.t('User account page');
      }
    });
  }
};

})(jQuery);
