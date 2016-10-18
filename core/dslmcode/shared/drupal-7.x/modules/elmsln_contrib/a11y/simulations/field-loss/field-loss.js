(function ($) {
  $(document).ready(function(){
    // on select list change simulate field loss when the state changes
    $('#a11y_sim_field_loss_select').change(function(){
      Drupal.a11y.simulatefieldLoss(this.value);
    });
    // throw these fields onto the front of the body
    $('body').prepend('<a id="a11y-sim-field-loss-close" href="#">' + Drupal.t('Disable simulation') + '</a><div id="a11y-sim-field-loss-area" class="z-depth-5"></div>');
    // close the simulation when we are done
    $('#a11y-sim-field-loss-close').click(function() {
      $('#a11y_sim_field_loss_select').val('');
      Drupal.a11y.simulatefieldLoss('');
    });
  });
  // fieldloss functionality
  Drupal.a11y.simulatefieldLoss = function(fieldloss){
    $("body").removeClass('a11y-sim-field-loss a11y-sim-field-loss-central a11y-sim-field-loss-peripheral');
    switch (fieldloss) {
      case '':
      break;
      case 'central':
        $("body").addClass('a11y-sim-field-loss a11y-sim-field-loss-central');
      break;
      case 'peripheral':
        $("body").addClass('a11y-sim-field-loss a11y-sim-field-loss-peripheral');
      break;
    }
  };
})(jQuery);