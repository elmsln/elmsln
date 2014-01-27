(function ($) {
    Drupal.behaviors.backtotop_admin = {
        attach: function(context) {
            $(document).ready(function() {
                $("#back_to_top_bg_color").farbtastic("#edit-back-to-top-bg-color");
                $("#back_to_top_border_color").farbtastic("#edit-back-to-top-border-color");
                $("#back_to_top_hover_color").farbtastic("#edit-back-to-top-hover-color");
                $("#back_to_top_text_color").farbtastic("#edit-back-to-top-text-color");
            });
        }
    };
})(jQuery);
