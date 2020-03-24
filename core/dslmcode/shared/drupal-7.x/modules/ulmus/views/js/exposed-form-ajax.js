/**
 * @file
 * Handles Views' exposed form AJAX data submission.
 */

(function ($) {
  'use strict';

  /**
   * Gets Form build info from settings and adds it to ajax data.
   *
   * @see views_exposed_form_ajax_enable().
   */
  Drupal.behaviors.ViewsExposedFormAjax = {
    attach: function (context, settings) {
      for (var ajaxObject in Drupal.ajax) {
        for (var name in Drupal.settings.ViewsExposedFormInfo) {
          if (Drupal.ajax[ajaxObject].options && Drupal.ajax[ajaxObject].options.data._triggering_element_name === name) {
            jQuery.extend(Drupal.ajax[ajaxObject].options.data, Drupal.settings.ViewsExposedFormInfo[name]);
          }
        }
      }
    }
  };

})(jQuery);
