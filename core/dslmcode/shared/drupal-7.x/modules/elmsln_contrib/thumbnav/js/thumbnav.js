(function ($) {
  // extend the drupal js object for function inclusion
  Drupal.thumbnav = Drupal.thumbnav || { functions: {} };
  // callback for swiping on the right side of screen
  Drupal.thumbnav.rightSideSwipe = function () {
    $('#thumbnav_controller_leftright').removeClass('thumbnav_controller_left').addClass('thumbnav_controller_right');
  };
  // callback for swiping on the right side of screen
  Drupal.thumbnav.leftSideSwipe = function () {
    $('#thumbnav_controller_leftright').removeClass('thumbnav_controller_right').addClass('thumbnav_controller_left');
  };
  // show leftright container
  Drupal.thumbnav.leftrightControllerShow = function () {
    $('#thumbnav_controller_leftright').addClass('thumbnav_controller_left');
  };
  // hide leftright container
  Drupal.thumbnav.leftrightControllerHide = function () {
    $('#thumbnav_controller_leftright').removeClass('thumbnav_controller_left');
  };
  // show left side
  Drupal.thumbnav.leftControllerShow = function () {
    $('#thumbnav_controller_left').addClass('thumbnav_controller_left');
  };
  // hide left side
  Drupal.thumbnav.leftControllerHide = function () {
    $('#thumbnav_controller_left').removeClass('thumbnav_controller_left');
  };
  // show right side
  Drupal.thumbnav.rightControllerShow = function () {
    $('#thumbnav_controller_right').addClass('thumbnav_controller_right');
  };
  // hide right side
  Drupal.thumbnav.rightControllerHide = function () {
    $('#thumbnav_controller_right').removeClass('thumbnav_controller_right');
  };
  // callback for resetting the control bar
  Drupal.thumbnav.hideController = function () {
    $('#thumbnav_controller_leftright').removeClass('thumbnav_controller_right').removeClass('thumbnav_controller_left');
  };
  // display simple modal
  Drupal.thumbnav.modal = function (title, text) {
    var output = '<h3>' + title + '</h3>';
    output += '<p>' + text + '</p>';
    $('#thumbnav_modal').html(output).addClass('display');
    $('#thumbnav_modal_close').addClass('display');
  }
  // hide modal
  Drupal.thumbnav.hideModal = function () {
    $('#thumbnav_modal').removeClass('display');
    $('#thumbnav_modal_close').removeClass('display');
  };
  $(document).ready(function(){
    // close modal when clicking elsewhere
    $('#thumbnav_modal_close').click(function(e) {
      Drupal.thumbnav.hideModal();
    });
  });
})(jQuery);