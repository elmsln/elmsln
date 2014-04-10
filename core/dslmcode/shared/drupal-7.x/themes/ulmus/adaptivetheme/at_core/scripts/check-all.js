/**
 * Just a wee script to give some nice check all check boxes to the
 * Unset CSS extension checkboxes, there can be a lot of them.
 */
(function ($) {
  Drupal.behaviors.ATcheckAll = {
    attach: function (context) {
      // Core
      $(":input[name=core_check_all]").click(function()
      {
        var checked_status = this.checked;
        $("input.drupal-core-css-file").each(function()
        {
          this.checked = checked_status;
        });
      });
      // Contrib
      $(":input[name=contrib_check_all]").click(function()
      {
        var checked_status = this.checked;
        $("input.contrib-module-css-file").each(function()
        {
          this.checked = checked_status;
        });
      });
      // Library
      $(":input[name=libraries_check_all]").click(function()
      {
        var checked_status = this.checked;
        $("input.library-css-file").each(function()
        {
          this.checked = checked_status;
        });
      });
      // User
      $(":input[name=explicit_check_all]").click(function()
      {
        var checked_status = this.checked;
        $("input.user-defined-css-file").each(function()
        {
          this.checked = checked_status;
        });
      });
    }
  };
})(jQuery);
