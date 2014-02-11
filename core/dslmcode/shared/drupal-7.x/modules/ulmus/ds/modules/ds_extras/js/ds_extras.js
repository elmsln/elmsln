/**
 * @file
 * Javascript functionality for the Display Suite Extras module.
 */

(function ($) {

// Switch view mode inline with AJAX, for the 'View mode switcher' option.
Drupal.behaviors.DSExtrasSwitchViewmode = {
  attach: function (context) {

    if ($('.switch-view-mode-field').length > 0) {
      $('.switch-view-mode-field a').click(function() {

        // Create an object.
        var link = $(this);

        // Get params from the class.
        var params = $(this).attr('class').split('-');

        $.ajax({
          type: 'GET',
          url: Drupal.settings.basePath + 'ds-switch-view-mode',
          data: {entity_type: params[0], view_mode: params[3], id: params[2]},
          dataType: 'json',
          success: function (data) {
            if (data.status) {
              old_view_mode = params[1];
              wrapper = link.parents('.view-mode-' + old_view_mode);
              Drupal.theme('DisplaySuiteSwitchViewmode', wrapper, data.content);
              Drupal.attachBehaviors();
            }
            else {
              alert(data.errorMessage);
            }
          },
          error: function (xmlhttp) {
            alert(Drupal.t('An HTTP error @status occurred.', {'@status': xmlhttp.status}));
          }
        });
        return false;
      });
    }
  }
};

/**
 * Theme function for a replacing content of Display Suite content wrapper.
 *
 * @param wrapper
 *   The HTML object which needs to be replaced
 * @param content
 *   The new content
 */
Drupal.theme.prototype.DisplaySuiteSwitchViewmode = function (wrapper, content) {
  wrapper.replaceWith(content);
};

})(jQuery);
