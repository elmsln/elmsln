Drupal.behaviors.securityReview = function(context) {
  $('.sec-rev-dyn').click(function() {
    anchor = $(this);
    row = $(this).parent().parent();
    $.getJSON(anchor.attr('href') + '&js=1', function(data) {
      if (data.skip == true) {
        anchor.text('Enable');
        row.attr('class' , 'info');
      }
      else if (data.result == 1) {
        anchor.text('Skip');
        row.attr('class' , 'ok');
      }
      else {
        anchor.text('Skip');
        row.attr('class' , 'error');
      }
    });
    return false;
  });
  
  $('.sec-rev-help-content').hide();
  $('.sec-rev-help-dyn').click(function() {
    $('.sec-rev-help-content').hide();
    $(this).parent().find('.sec-rev-help-content').show();
  });
}
