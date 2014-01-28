(function ($) {
  $(document).ready(function(){
    // on swipe from off screen, display controller
    $$('#regions_right_slideout .regions_block_content').swipeRight(function(){
      $('#regions_right_slideout .regions_pre_block_container').click();
    });
  });
})(jQuery);