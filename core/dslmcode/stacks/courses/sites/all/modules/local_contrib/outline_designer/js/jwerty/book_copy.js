(function ($) {
  // duplicate
  jwerty.key('ctrl+shift+D', function () {
    if (Drupal.settings.outline_designer.activeNid == '') {
      $('#book-admin-edit div.context-menu-item-inner').click();
    }
    else {
      Drupal.outline_designer.form_render('book_copy');
    }
  });
})(jQuery);