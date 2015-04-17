// $Id$

/**
 * Admin menu dropdown behavior.
 */
(function($){
  Drupal.behaviors.adminMenuDropDown = {
    attach: function (context, settings) {
      // Initialize settings.
      settings.admin_menu_dropdown = $.extend({
        onload: false,
        key: '`'
      }, settings.admin_menu_dropdown || {});

      $('#admin-menu').once(function () {
        // Attach to keypress event.
        $(document).keypress(function(e) {
          var unicode = e.keyCode? e.keyCode : e.charCode;
          if (String.fromCharCode(unicode) == settings.admin_menu_dropdown.key) {
            $('#admin-menu').slideToggle('fast');
            // TODO: Maybe animate the margin change so its not so jumpy?
            $('body').toggleClass('adm_menu_hidden');
          }
        });
        if (settings.admin_menu_dropdown.onload) {
          // Initially hide admin menu.
          $(this).hide();
          $('body').addClass('adm_menu_hidden');
        }
      });
    }
  }
})(jQuery);
