/**
 * Utility that makes it possible to hide fields when a checkbox is unchecked
 */
(function ($) {
  function setupHiding () {
    var $toggler = $(this);

    // Getting the field which should be hidden:
    var $subject = $($toggler.data('h5p-visibility-subject-selector'));

    var toggle = function () {
      $subject.toggle($toggler.is(':checked'));
    };

    $toggler.change(toggle);
    toggle();
  }

  $(document).ready(function () {
    // Get the checkboxes making other fields being hidden:
    $('.h5p-visibility-toggler').each(setupHiding);
  });
})(H5P.jQuery);
