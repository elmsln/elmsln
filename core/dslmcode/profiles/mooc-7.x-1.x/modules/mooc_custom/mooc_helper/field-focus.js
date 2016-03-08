/**
 * Allow for auto selection of iframe content area on focus
 */
(function ($) {
  Drupal.behaviors.mooc_helper_node_form = {
    attach: function(context) {
      // set title as focus field when we're creating a new item
      $('#edit-title').focus();
    }
  };
})(jQuery);