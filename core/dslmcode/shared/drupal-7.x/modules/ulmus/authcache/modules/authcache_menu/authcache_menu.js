(function (Drupal, $) {
  "use strict";

  var tabs_container, actions_container;

  function displayContainerIfNotEmpty(container) {
    if (!/\S/.test(container.text())) {
      container.hide();
    }
    else {
      container.show();
    }
  }

  Drupal.behaviors.authcacheMenuFragments = {
    attach: function (context, settings) {
      if (typeof tabs_container === 'undefined') {
        tabs_container = $('.tabs');
      }
      displayContainerIfNotEmpty(tabs_container);

      if (typeof actions_container === 'undefined') {
        actions_container = $('.action-links');
      }
      displayContainerIfNotEmpty(actions_container);
    }
  };

}(Drupal, jQuery));
