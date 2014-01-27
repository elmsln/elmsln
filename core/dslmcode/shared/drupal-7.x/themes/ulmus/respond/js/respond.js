/**
 * @todo
 */

(function($) {
  /**
   * This is needed for a little extra flexibility in defining our default active menu item
   * if Drupal isn't by default. If nothing is labeled as active, then we'll make the first link 
   * active (which is usually the home link
   */
  Drupal.behaviors.respondActiveMenu = {
    attach: function (context) {
      var activeMenu = $('nav ul.main-menu li.active, nav ul.main-menu li.active-trail').size();
      console.log(activeMenu);
      if (activeMenu == '0') {
        $('nav ul.main-menu li:first-child').addClass('active').children('a:first-child').addClass('active');
      }
    }
  };
})(jQuery);