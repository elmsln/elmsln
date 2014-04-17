/**
 * @file
 * CIS LMS-less helper for top bar
 */
(function ($) {
  /**
   * Apply margin to page.
   *
   * Note that directly applying marginTop does not work in IE. To prevent
   * flickering/jumping page content with client-side caching, this is a regular
   * Drupal behavior.
   */
  Drupal.behaviors.lmsLessBar = {
    attach: function(context, settings) {
      // On option change, switch location
      $('select.cis-lmsless-bar-services').change(function(){
        window.location = $(this).val();
      });
    }
  };
  /**
   * Apply margin to page.
   *
   * Note that directly applying marginTop does not work in IE. To prevent
   * flickering/jumping page content with client-side caching, this is a regular
   * Drupal behavior.
   */
  Drupal.behaviors.lmsLessBarMarginTop = {
    attach: function (context, settings) {
      if (typeof settings.admin_menu != 'undefined' && !settings.admin_menu.suppress && settings.admin_menu.margin_top) {
        $('body:not(.cis-lmsless-admin-margin)', context).addClass('cis-lmsless-admin-margin');
        $('body', context).removeClass('admin-menu');
      }
      else {
        $('body:not(.cis-lmsless-margin)', context).addClass('cis-lmsless-margin');
      }
    }
  };

})(jQuery);
