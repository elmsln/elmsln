(function($) {
  Drupal.behaviors.accessibilityTheming = {

    messages : {},
    
    attach : function(context) {
      this.addToggle();
    },

    addToggle : function() {
      var that = this;
      $('body').append('<div id="accessibility-theming"><input type="checkbox" id="accessibility-theming-checkbox"><label for="accessibility-theming-checkbox">' + Drupal.t('Accessibility theming') + '</label></div>');
      $('#accessibility-theming-checkbox').change(function() {
        if ($(this).is(':checked')) {
          that.checkPage();
        }
        else {
          Drupal.accessibility.cleanUpHighlight();
          Drupal.accessibility.errorConsole.hide();
          $('body').removeClass('accessibility-theming-checked');
        }
      })
    },

    checkPage : function() {
      if ($('body').hasClass('accessibility-theming-checked')) {
        return;
      }
      $('body').addClass('accessibility-theming-checked');
      Drupal.accessibility.checkElement($('body'));
    }
  }
})(jQuery);
