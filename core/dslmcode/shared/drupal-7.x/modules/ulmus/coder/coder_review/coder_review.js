/**
 * Javascript for the Coder_review module.
 */

(function ($) {
  jQuery.fn.extend({
    check : function() { return this.each(function() { this.checked = true; }); },
    uncheck : function() { return this.each(function() { this.checked = false; }); }
  });

  Drupal.behaviors.coderReviewFormHandler = {
    attach: function (context) {
      $("input:checkbox").click(
        function() {
          core = this.form.elements.namedItem("edit-coder-core");
          active = this.form.elements.namedItem("edit-coder-active-modules");
          if (this == core || this == active) {
            modules = "input[id^=edit-coder-modules-]";
            themes = "input[id^=edit-coder-themes-]";
            if (core.checked || active.checked) {
              $(modules).uncheck();
              $(themes).uncheck();
              if (core.checked) {
                modules += '.coder-core';
                themes += '.coder-core';
              }
              if (active.checked) {
                modules += '.coder-active';
                themes += '.coder-active';
              }
              $(modules).check();
              $(themes).check();
            }
            else {
              if (this == active) {
                modules += ".coder-active";
                themes += ".coder-active";
              }
              else {
                modules += ".coder-core";
                themes += ".coder-core";
              }
              $(modules).uncheck();
              $(themes).uncheck();
            }
          }
          else if (this.id.substr(0, 19) == "edit-coder-modules-" || this.id.substr(0, 18) == "edit-coder-themes-") {
            core.checked = false;
            active.checked = false;
          }
          return true;
        }
      );
      $("img.coder-more").click(
        function() {
          $('.coder-description', this.parentNode).slideToggle();
        }
      );
    }
  };
})(jQuery);
