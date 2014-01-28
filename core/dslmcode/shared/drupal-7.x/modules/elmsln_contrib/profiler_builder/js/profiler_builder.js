// JavaScript Document
(function ($) {
  $(document).ready(function(){
    $('#edit-profile-machine-name').parents('.form-item').hide();
    $('#edit-name').bind('keyup change', function() {
      var machine = $(this).val().toLowerCase().replace(/[^a-z0-9]+/g, '_').replace(/_+/g, '_');
      if (machine !== '_' && machine !== '') {
        $('#edit-profile-machine-name').val(machine);
        $('#edit-name').next().empty().append(' Machine name: ' + machine + ' [').append($('<a href="#">'+ Drupal.t('Edit') +'</a>').click(function() {
          $('#edit-profile-machine-name').parents('.form-item').show();
          $('#edit-profile-machine-name').next().hide();
          $('#edit-name').unbind('keyup');
          return false;
        })).append(']');
      }
      else {
        $('#edit-profile-machine-name').val(machine);
        $('#edit-profile-machine-name').next().text('');
      }
    });
    $('#edit-name').keyup();
  });
})(jQuery);