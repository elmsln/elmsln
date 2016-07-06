/**
 * Focus on the title field when the frame loads
 */
(function ($) {
  $(document).ready(function(){
    // set title as focus field when we're creating a new item
    $('#edit-title').focus();
  });
})(jQuery);