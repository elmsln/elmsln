(function ($) {

/**
 * Prevents submit button double-click on replace confirmation form.
 */
Drupal.behaviors.hideSubmitButton = {
  attach: function(context) {
    $('input#edit-confirm').click(function() {
      $('.scanner-buttons').css('position','relative')
        .append('<div class="scanner-button-msg"><p>Replacing items... please wait...</p></div>')
      $('.scanner-button-msg').click(function() { return false; });
      return true;
    });
  }
};

})(jQuery);
