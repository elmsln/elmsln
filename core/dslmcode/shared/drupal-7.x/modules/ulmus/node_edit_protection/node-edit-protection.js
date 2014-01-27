(function($) {
  Drupal.node_edit_protection = {};
  var click = false; // Allow Submit/Edit button
  var edit = false; // Dirty form flag

  Drupal.behaviors.nodeEditProtection = {
    attach : function(context) {
      // If they leave an input field, assume they changed it.
      $(".node-form :input").each(function() {
        $(this).blur(function() {
          edit = true;
        });
      });

      // Let all form submit buttons through
      $(".node-form input[type='submit']").each(function() {
        $(this).addClass('node-edit-protection-processed');
        $(this).click(function() {
          click = true;
        });
      });

      // Catch all links and buttons EXCEPT for "#" links
      $("a, button, input[type='submit']:not(.node-edit-protection-processed)")
          .each(function() {
            $(this).click(function() {
              // return when a "#" link is clicked so as to skip the
              // window.onbeforeunload function
              if (edit && $(this).attr("href") != "#") {
                return 0;
              }
            });
          });

      // Handle backbutton, exit etc.
      window.onbeforeunload = function() {
        // Add CKEditor support
        if (typeof (CKEDITOR) != 'undefined' && typeof (CKEDITOR.instances) != 'undefined') {
          for ( var i in CKEDITOR.instances) {
            if (CKEDITOR.instances[i].checkDirty()) {
              edit = true;
              break;
            }
          }
        }
        if (edit && !click) {
          click = false;
          return (Drupal.t("You will lose all unsaved work."));
        }
      }
    }
  };
})(jQuery);
