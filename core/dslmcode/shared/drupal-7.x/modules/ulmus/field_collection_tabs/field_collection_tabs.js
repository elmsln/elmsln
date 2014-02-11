/**
 * @file
 * Provides js for tabs
 * @copyright Copyright(c) 2012 Previous Next Pty Ltd
 * @license GPL v2 http://www.fsf.org/licensing/licenses/gpl.html
 * @author Lee Rowlands larowlan at previousnext dot com dot au
 */


(function ($) {
/**
 * JS related to the tabs.
 */
Drupal.behaviors.fieldCollectionTabs = {
  attach: function (context) {

    $('.field-collection-tabs', context)
      .once('.tabs-processed')
      .tabs();
  }
};

})(jQuery);


