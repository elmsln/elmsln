(function ($) {
  Drupal.behaviors.cleCritique = {
    attach: function (context, settings) {
      // Make the critique feedback float.
      var formSelector = '#cle-critique-node-form';
      var feedbackSelector = '#cle-critique-node-form .field-name-field-cle-crit-feedback';
      $(formSelector).each(function() {
        $(feedbackSelector).pushpin({ top: $(formSelector).offset().top });
      });

      // Add hide button.
      $('#cle-critique-node-form .field-name-field-cle-crit-feedback').prepend('<a aria-label="Close Feedback form" class="cle-critique__hide-feedback">Hide Critique Form <i class="material-icons">visibility_off</i></a>');

      // hide functionality.
      $('.cle-critique__hide-feedback').click(function() {
        var parent = $(this).parents(feedbackSelector);
        if (parent.hasClass('is-closed')) {
          $(this).html('Hide Critique Form <i class="material-icons">visibility_off</i>');
        }
        else {
          $(this).html('Show Critique Form <i class="material-icons">visibility</i>');
        }
        // toggle the is-closed class
        parent.toggleClass('is-closed');
      });
    }
  };
}(jQuery));

