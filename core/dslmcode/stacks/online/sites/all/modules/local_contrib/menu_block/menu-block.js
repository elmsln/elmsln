(function ($) {

Drupal.behaviors.menu_block = {
  attach: function (context, settings) {
    // This behavior attaches by ID, so is only valid once on a page.
    if ($('#menu-block-settings.menu-block-processed').size()) {
      return;
    }
    $('#menu-block-settings', context).addClass('menu-block-processed');

    // Show the "display options" if javascript is on.
    $('.form-item-display-options.form-type-radios>label', context).addClass('element-invisible');
    $('.form-item-display-options.form-type-radios', context).show();
    // Make the radio set into a jQuery UI buttonset.
    $('#edit-display-options', context).buttonset();

    // Override the default show/hide animation for Form API states.
    $('#menu-block-settings', context).bind('state:visible', function(e) {
      if (e.trigger) {
        e.stopPropagation() /* Stop the handler further up the tree. */
        $(e.target).closest('.form-item, .form-wrapper')[e.value ? 'slideDown' : 'slideUp']('fast');
      }
    });

    // Syncronize the display of menu and parent item selects.
    $('.menu-block-parent-mlid', context).change( function() {
      var menuItem = $(this).val().split(':');
      $('.menu-block-menu-name').val(menuItem[0]);
    });
    $('.menu-block-menu-name', context).change( function() {
      $('.menu-block-parent-mlid').val($(this).val() + ':0');
    });
  }
};

})(jQuery);
