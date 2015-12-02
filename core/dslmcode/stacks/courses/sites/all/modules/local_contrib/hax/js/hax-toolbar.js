(function ($) {
  $(document).ready(function() {
    // handle click on submit button so that we populate the body area at that time
    // this way we save what was loaded into the page
    $('#hax-page-edit-form').submit(function(event) {
      // trap form being empty and block submission
      // @todo things
      if ($('#edit-hax-body').val() == null) {
        event.preventDefault();
      }
      $('#edit-hax-body').val($('.hax-body').html());
      $('#hax-page-edit-form').submit();
    });
    // create toolbar buttons for appending items to the interface
    $('.hax-toolbar-tool').click(function(){
      var tool = $(this).attr('data-hax-tool');
      var container = $.parseHTML(Drupal.settings.hax[tool]['markup']);
      // load first item of the container to add actions to
      container[0].setAttribute('data-guid', Drupal.hax.getGUID());
      // easiest use-case, insert the markup we have
      if (Drupal.settings.hax[tool]['action'] == 'insert') {
        // see if this is a container or content
        if (Drupal.settings.hax[tool]['type'] == 'row') {
          Drupal.hax.applyDrop(container[0]);
          Drupal.hax.applyDrag(container[0]);
        }
        else if (Drupal.settings.hax[tool]['type'] == 'column') {
          Drupal.hax.applyDrop(container[0]);
        }
        else {
          Drupal.hax.applyDrag(container[0]);
        }
        Drupal.hax.applyEventListeners(container[0]);
        var prependto = '';
        for (var len = Drupal.hax.selections.activeitems.length, i = 0; i < len; i++) {
          // drop item after the current one in the same parent
          if (Drupal.hax.selections.activeitems[i].getAttribute('data-draggable') == 'item') {
            prependto = 'item';
            $(container[0]).prependTo(Drupal.hax.selections.activeitems[i].parentNode);
            // @todo need to reorder so it's not at the end of this parent
          }
          else if (Drupal.hax.selections.activeitems[i].getAttribute('data-draggable') == 'target') {
            prependto = 'target';
            $(container[0]).prependTo(Drupal.hax.selections.activeitems[i]);
          }
        }
        // didn't find any targets so just stick it to the body in general
        if (prependto == '') {
          $(container[0]).prependTo('.hax-body');
        }
        $('#edit-hax-body').val($('.hax-body').html());
      }
    });
  });
})(jQuery);