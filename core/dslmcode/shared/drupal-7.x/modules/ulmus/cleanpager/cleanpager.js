(function ($) {

  Drupal.behaviors.cleanpager = {
    attach : function(context, settings) {
      $('.pager a:not(.cleanpager-handled)', context).addClass('cleanpager-handled').each( function() {
        $(this).text($(this).text().replace(/Visit(.*)Page /,''));
      });
    }
  };

})(jQuery);
