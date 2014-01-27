(function ($) {

/**
 * Provide the summary information for the language plugin's vertical tab.
 */
Drupal.behaviors.menuPositionLanguageSettingsSummary = {
  attach: function (context) {
    $('fieldset#edit-language', context).drupalSetSummary(function (context) {
      return $('select[name="language"] option:selected', context).text();
    });
  }
};

})(jQuery);
