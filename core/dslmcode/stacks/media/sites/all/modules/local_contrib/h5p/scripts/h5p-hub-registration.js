/* global Drupal */
(function ($) {
  Drupal.behaviors.H5PContentHubRegistration = {
    attach: function (context, settings) {
      const data = settings.H5PContentHubRegistration;
      data.container = document.getElementById('h5p-hub-registration');
      H5PHub.createRegistrationUI(data);
    }
  }
})(jQuery);
