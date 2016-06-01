(function (drupalSettings, navigator, window) {

  'use strict';

  if (!('serviceWorker' in navigator)) {
    return;
  }

  navigator.serviceWorker.register(drupalSettings.pwa.path, {scope: '/'})
    .then(function () { })
    .catch(function (error) {
      // Something went wrong.
    });

  // Reload page when user is back online on a fallback offline page.
  window.addEventListener('online', function () {
    var loc = window.location;
    // If the page serve is the offline fallback, try a refresh when user
    // get back online.
    if (loc.pathname !== '/offline' && document.querySelector('[data-drupal-pwa-offline]')) {
      loc.reload();
    }
  });

  /*
  In case you want to unregister the SW during testing:

  navigator.serviceWorker.getRegistration()
    .then(function(registration) {
      registration.unregister();
    });

   */

}(Drupal.settings, navigator, window));
