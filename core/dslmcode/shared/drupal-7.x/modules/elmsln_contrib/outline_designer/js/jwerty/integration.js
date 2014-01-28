(function ($) {
  /* KEYBOARD BASED NAVIGATION */
  // paging capabilities up through items
  jwerty.key('shift+up', function() {
    // need something selected
    if (Drupal.settings.outline_designer.activeNid != '') {
      // test that there is an item there first to avoid busting out top of table
      if ($('#node-' + Drupal.settings.outline_designer.activeNid).parent().parent().prev().children().children('img').length != 0) {
        Drupal.outline_designer.set_active($('#node-' + Drupal.settings.outline_designer.activeNid).parent().parent().prev().children().children('img')[1]['id']);
      }
    }
  });
  // paging capabilities down through items
  jwerty.key('shift+down', function() {
    // need something selected or start at 1st
    if (Drupal.settings.outline_designer.activeNid != '') {
      // test that we don't go below the outline itself
      if ($('#node-' + Drupal.settings.outline_designer.activeNid).parent().parent().next().children().children('img').length != 0) {
        // test if we should automatically open a container
        if ($('#collapse-' + Drupal.settings.outline_designer.activeNid).attr('alt') == 'closed') {
          $('#collapse-' + Drupal.settings.outline_designer.activeNid).click();
        }
        Drupal.outline_designer.set_active($('#node-' + Drupal.settings.outline_designer.activeNid).parent().parent().next().children().children('img')[1]['id']);
      }
    }
    else {
      // make sure there's anything at all on the page
      if ($('#book-outline').children('tbody').children().children().children('img').length != 0) {
        Drupal.outline_designer.set_active($('#book-outline').children('tbody').children().children().children('img')[1]['id']);
      }
    }
  });
  // allow for selection of an item to work on
  jwerty.key('ctrl+shift+right', function() {
    // need something selected
    if (Drupal.settings.outline_designer.activeNid != '') {
      // only supply item focus once
      if (!$('#node-' + Drupal.settings.outline_designer.activeNid).prev().prev().hasClass('od_has_focus')) {
        $('#node-' + Drupal.settings.outline_designer.activeNid).prev().prev().focus();
        $('#node-' + Drupal.settings.outline_designer.activeNid).prev().prev().addClass('od_has_focus');
        // when moving items around everything needs to be visible
        $('.od-open-all').click();
      }
    }
  });
  // shortcut to first item
  jwerty.key('ctrl+shift+F', function () {
    // make sure there's anything at all on the page
    if ($('#book-outline').children('tbody').children().children().children('img').length != 0) {
      Drupal.outline_designer.set_active($('#book-outline').children('tbody').children().children().children('img')[1]['id']);
    }
  });
})(jQuery);