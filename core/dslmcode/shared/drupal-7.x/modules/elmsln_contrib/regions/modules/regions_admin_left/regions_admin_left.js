(function ($) {
  $(document).ready(function(){
  //establish the default state for the nav which is closed
    $('#regions_admin_left .regions_pre_block_container') .addClass('regions_toggle_closed');
    //when clicking the title, bring it to the front
    $('#regions_admin_left .regions_pre_block_container').click(function(){
      if ($(this).hasClass('regions_toggle_closed')) {
        $(this).addClass('regions_toggle_open');
        $(this).removeClass('regions_toggle_closed');
        $('#regions_admin_left').animate({left:'0'}, 'fast');
      }
      else {
        $(this).addClass('regions_toggle_closed');
        $(this).removeClass('regions_toggle_open');
        $('#regions_admin_left').animate({left:'-225px'}, 'fast');
      }
    });
    // scroll to keep visible
  });
  // ensure that regions aren't displayed under other items after overlay mode
  $(document).bind('drupalOverlayBeforeClose', function(){
    $('#regions_admin_left').css('z-index', '');
  });
  // ensure that regions aren't displayed over the overlay
  $(document).bind('drupalOverlayBeforeLoad', function(){
    $('#regions_admin_left').css('z-index', '500');
  });
  var timer;
  $(window).bind('scroll',function () {
      clearTimeout(timer);
      timer = setTimeout( refresh , 150 );
  });
  var refresh = function () { 
    var region_height = $('#regions_admin_left .regions_block_container').height();
    var window_height = $(window).height();
    if (window_height > region_height) {
      $('#regions_admin_left').css('position', 'fixed');
    }
    else {
      $('#regions_admin_left').css('position', 'absolute');
    }
  };
})(jQuery);