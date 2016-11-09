var bpnFlickrCount = 0;

(function ($) {

  Drupal.behaviors.bulkphotonode = {
    attach:function(context, settings) {

      bpnFlickrCount = parseInt($('.bpn-flickr-count').text());

      // Hide update button for folks with JS enabled
      $('#edit-photo-container-selector-update').hide();

      // Auto-submit on change for the select menu
      $('#edit-photo-container-selector-photo-container-type').change(function() {
        $('#bpn-flickr-form, #bpn-flickr-private-form').submit();
      });

      // Labels were being weird, fixes multiple events being triggered.
      $('.bpn-flickr-thumbnail label').removeAttr('for');

      // Click anywhere on thumbnail to check the image's checkbox.
      $('.bpn-flickr-thumbnail').click(function() {
        checkbox = $(this).find('input');
        checkbox.attr('checked', !checkbox.attr('checked'));
        checkbox.change();
      });

      $('#edit-photostream input[type=checkbox]').change(function() {
        if ($(this).is(':checked')) {
          bpnFlickrCount++;
          $(this).parent().parent().parent().addClass('selected');
        }
        else {
          bpnFlickrCount--;
          $(this).parent().parent().parent().removeClass('selected');
        }
        $('.bpn-flickr-count').text(bpnFlickrCount);

      }).click(function(event){
        event.stopPropagation();
      });

    } // attach

  }; // Drupal.behaviors.bulkphotonode

})(jQuery);
