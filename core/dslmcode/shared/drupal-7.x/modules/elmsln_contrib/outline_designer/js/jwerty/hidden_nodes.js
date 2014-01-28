(function ($) {
  // hide an item
  jwerty.key('ctrl+shift+H', function () {
    if (Drupal.settings.outline_designer.activeNid != '') {
      Drupal.outline_designer.form_render('hidden_nodes');
    }
  });
})(jQuery);