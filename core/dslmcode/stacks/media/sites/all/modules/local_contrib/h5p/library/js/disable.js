(function ($) {
  $(document).ready(function () {
    var $inputs = $('.h5p-action-bar-settings input');
    var $frame = $inputs.filter('input[name="frame"], input[name="h5p_frame"]');
    var $others = $inputs.filter(':not(input[name="frame"], input[name="h5p_frame"])');

    var toggle = function () {
      if ($frame.is(':checked')) {
        $others.attr('disabled', false);
      }
      else {
        $others.attr('disabled', true);
      }
    };

    $frame.change(toggle);
    toggle();
  });
})(H5P.jQuery);
