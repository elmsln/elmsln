(function ($) {

/**
 * Behavior to disable the "unflag" option if "flag" is not available.
 */
Drupal.behaviors.flagRoles = {};
Drupal.behaviors.flagRoles.attach = function(context) {
  $('#flag-roles input.flag-access', context).change(function() {
    var unflagCheckbox = $(this).parents('tr:first').find('input.unflag-access').get(0);
    if (this.checked) {
      // If "flag" is available, restore the state of the "unflag" checkbox.
      unflagCheckbox.disabled = false;
      if (typeof(unflagCheckbox.previousFlagState) != 'undefined') {
        unflagCheckbox.checked = unflagCheckbox.previousFlagState;
      }
      else {
        unflagCheckbox.checked = true;
      }
    }
    else {
      // Remember if the "unflag" option was checked or unchecked, then disable.
      unflagCheckbox.previousFlagState = unflagCheckbox.checked;
      unflagCheckbox.disabled = true;
      unflagCheckbox.checked = false;
    }
  });

  $('#flag-roles input.unflag-access', context).change(function() {
    if ($(this).parents('table:first').find('input.unflag-access:enabled:not(:checked)').size() == 0) {
      $('div.form-item-unflag-denied-text').slideUp();
    }
    else {
      $('div.form-item-unflag-denied-text').slideDown();
    }
  });

  // Hide the link options by default if needed.
  if ($('#flag-roles input.unflag-access:enabled:not(:checked)').size() == 0) {
    $('div.form-item-unflag-denied-text').css('display', 'none');
  }
};

/**
 * Vertical tabs integration.
 */
Drupal.behaviors.flagSummary = {};

Drupal.behaviors.flagSummary.attach = function (context) {
  $('fieldset.flag-fieldset', context).drupalSetSummary(function(context) {
    var flags = [];
    $('input:checkbox:checked', context).each(function() {
      flags.push(this.title);
    });

    if (flags.length) {
      return flags.join(', ');
    }
    else {
      return Drupal.t('No flags');
    }
  });
};

})(jQuery);
