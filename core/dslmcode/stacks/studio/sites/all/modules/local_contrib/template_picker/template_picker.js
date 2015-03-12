/**
 * @file
 * Attaches behaviors for the template picker module.
 */

(function ($) {

Drupal.behaviors.templatePickerFieldsetSummaries = {
  attach: function (context) {
    $('fieldset.template-picker-form', context).drupalSetSummary(function (context) {
      return Drupal.checkPlain($('.form-item-template-picker select option:selected').text());
    });
  }
};

})(jQuery);
