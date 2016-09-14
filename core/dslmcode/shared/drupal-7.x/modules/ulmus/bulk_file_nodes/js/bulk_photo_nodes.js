jQuery(document).ready(function($) {
  $('#bpn-flickr-form').ajaxStart(function(){
    $('#edit-override-fields-finish').attr('disabled', 'disabled');
  });
  $('#bpn-flickr-form').ajaxSuccess(function(){
    $('#edit-override-fields-finish').removeAttr('disabled');
  });
});
