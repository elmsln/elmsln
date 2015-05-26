/**
 * @file
 * Helper to insert icor clicked object references into ckeditor.
 */
(function($) {
  $(document).ready(function(){
    $('body').append('<input id="asset-clicked" type="hidden" value="0" />');
    $('.icor-asset-insert').click(function(){
      $('#asset-clicked').val($(this).attr('id').replace('icor-insert-', ''));
      //when they click ok, do it that way, it's too hard to target it seems
      window.parent.document.querySelector('[class="cke_dialog_ui_button"]').click();
    });
  });
})(jQuery);
