(function ($) {  
  /* USABILITY SHORTCUTS */
  
  // shortcut to increase size
  jwerty.key("ctrl+shift+=", function () {
    $('.od-increase').click();
  });
  
  // shortcut to open all items
  jwerty.key("ctrl+shift+'", function () {
    $('.od-open-all').click();
  });
  
  // shortcut to close all items
  jwerty.key("ctrl+shift+;", function () {
    $('.od-close-all').click();
  });
  
  /* OPERATION SHORTCUTS */
  
  // add content
  jwerty.key('ctrl+shift+A', function () {
    if (Drupal.settings.outline_designer.activeNid == '') {
      $('#book-admin-edit div.context-menu-item-inner').click();
    }
    else {
      Drupal.outline_designer.form_render('add_content');
    }
  });
  // rename an item
  jwerty.key('ctrl+shift+R', function () {
    if (Drupal.settings.outline_designer.activeNid != '') {
      Drupal.outline_designer.form_render('rename');
    }
  });
})(jQuery);