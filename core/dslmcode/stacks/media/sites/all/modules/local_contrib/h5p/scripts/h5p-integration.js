/* global Drupal */
(function ($) { // Avoid leaking variables

  /**
   * Add CSRF token to link
   *
   * @param {HTMLAnchorElement} button Link
   * @param {string} token Token
   */
  const addCSRFToken = function (button, token) {
    const form = document.createElement('form');
    form.action = button.href;
    form.method = 'POST';
    form.classList.add('h5p-hidden-form');

    const inputToken = document.createElement('input');
    inputToken.name = '_token';
    inputToken.type = 'hidden';
    inputToken.value = token;
    form.appendChild(inputToken);

    button.parentNode.appendChild(form);

    button.href = '#' + button.href.match(/([^\/])+$/i)[0];
    button.addEventListener('click', function (e) {
      form.submit();
      e.preventDefault();
    });
  }

  Drupal.behaviors.h5pContentHub = {
    attach: function (context, settings) {
      if (typeof context.getElementsByClassName === "function") {
        const buttons = context.getElementsByClassName('h5p-content-hub-button');
        for (let i = 0; i < buttons.length; i++) {
          if (buttons[i].classList.contains('processed')) {
            continue; // Skip
          }
          buttons[i].classList.add('processed');
          addCSRFToken(buttons[i], settings.h5pContentHub.token);
        }
      }
    }
  };

})(jQuery);
