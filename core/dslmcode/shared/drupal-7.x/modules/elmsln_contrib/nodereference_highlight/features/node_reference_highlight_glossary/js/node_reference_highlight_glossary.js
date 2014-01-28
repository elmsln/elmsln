// JavaScript Document
(function($) {
  $(document).ready(function(){
    $('.node .nrhi_body_item').click(function(){
      // remove class from all potentially active rows
      $('.view-nrhi-term-glossary .views-row').removeClass('nrhi-active-term');
      // highlight the clicked item only
      $('.view-nrhi-term-glossary .views-row a[name="' + $(this).attr('href').replace('#','') + '"]').parent().parent().parent().addClass('nrhi-active-term');
      $('#regions_right_slideout #regions_block_views_nrhi_term_glossary-block_1 .regions_block_title').click();
    });
    // auto close the right slide out when clicking return
    $('#regions_right_slideout .nrhi_return').click(function(){
      $('#regions_right_slideout .regions_pre_block_container').click();
    });
    $('#regions_right_slideout .regions_pre_block_container').click(function(){
     $('.view-nrhi-term-glossary .views-row').removeClass('nrhi-active-term');
    });
  });
})(jQuery);