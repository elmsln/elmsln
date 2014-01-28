(function ($) {
$(document).ready(function(){
  // block 1 is the default for an open
  $('#regions_right_slideout .regions_1 .regions_block_content').css('display','block');
  // establish the default state for the nav which is closed
  $('#regions_right_slideout .regions_pre_block_container').addClass('regions_toggle_closed');
  // when clicking the title, bring it to the front
  $('#regions_right_slideout .regions_block_title').click(function(){
    // hide all block content
    $('#regions_right_slideout .regions_block_content').css('display','none');
    // show this one
    $(this).parent().children('.regions_block_content').css('display','block');
    // only expand based on clicking block titles, never collapse
    if ($('#regions_right_slideout .regions_pre_block_container').hasClass('regions_toggle_closed')) {
      $('#regions_right_slideout .regions_pre_block_container').addClass('regions_toggle_open');
      $('#regions_right_slideout .regions_pre_block_container').removeClass('regions_toggle_closed');
      $('#regions_right_slideout').animate({right:'0'}, 'fast');
    }
  });
  // collapse based on toggle
  $('#regions_right_slideout .regions_pre_block_container').click(function(){
    // additional logic is to account for menu being opened by clicking a block title
    if ($(this).hasClass('regions_toggle_closed')) {
      $(this).addClass('regions_toggle_open');
      $(this).removeClass('regions_toggle_closed');
      $('#regions_right_slideout').animate({right:'0'}, 'fast');
    }
    else {
      $(this).addClass('regions_toggle_closed');
      $(this).removeClass('regions_toggle_open');
      var width = $(window).width();
      // allow for responsive snap point
      if (width < 960) {
        $('#regions_right_slideout').animate({right:'-50%'}, 'fast', 'linear', function(){ $('#regions_right_slideout').css('right', '')});
      }
      else {
        $('#regions_right_slideout').animate({right:'-30%'}, 'fast', 'linear', function(){ $('#regions_right_slideout').css('right', '')});
      }
    }
  });
  // integration with node reference highlight
  $('.nrhi_body_item').click(function(){
    $('#'+ $(this).attr('name').replace('_body_item', '')).parent().click();
  });
});
  // ensure that regions aren't displayed under other items after overlay mode
  $(document).bind('drupalOverlayBeforeClose', function(){
    $('#regions_right_slideout').css('z-index', '');
  });
  // ensure that regions aren't displayed over the overlay
  $(document).bind('drupalOverlayBeforeLoad', function(){
    $('#regions_right_slideout').css('z-index', '500');
  });
})(jQuery);