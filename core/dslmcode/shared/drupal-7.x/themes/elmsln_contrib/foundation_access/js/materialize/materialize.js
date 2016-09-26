(function($) {
'use strict';
  Drupal.settings.activeSideNav = null;
  // apply all the materialize javascript
  Drupal.behaviors.materializeJS = {
    attach: function(context) {
      $('select').not('.chosen').not('.cke_dialog_body select').material_select();
      $('.parallax').parallax();
      $('.carousel').not('.carousel-slider').carousel();
      $('.collapsible').collapsible({
        accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
      });
      $('.carousel-slider').carousel({full_width: true});
      $('.elmsln-right-side-nav-trigger').bind('click', function() {
          $('#' + $(this).attr('data-activates')).removeClass('elmsln-modal-hidden').focus();
          Drupal.settings.activeSideNav = $(this).attr('data-activates');
        }).sideNav({
        menuWidth: 400, // Default is 240
        edge: 'right', // Choose the horizontal origin
        closeOnClick: false // Closes side-nav on <a> clicks, useful for Angular/Meteor
      });
      $('.elmsln-left-side-nav-trigger').bind('click', function() {
          $('#' + $(this).attr('data-activates')).removeClass('elmsln-modal-hidden').focus();
          Drupal.settings.activeSideNav = $(this).attr('data-activates');
        }).sideNav({
        menuWidth: 280, // Default is 240
        edge: 'left', // Choose the horizontal origin
        closeOnClick: false // Closes side-nav on <a> clicks, useful for Angular/Meteor
      });
      $('.elmsln-modal-trigger').bind('click', function() {
        // hide all currently visible modals
        $('.close-reveal-modal:visible').trigger('click');
      }).leanModal({
        dismissible: true, // Modal can be dismissed by clicking outside of the modal
        opacity: .5, // Opacity of modal background
        in_duration: 150, // Transition in duration
        out_duration: 50, // Transition out duration
        starting_top: '1rem', // Starting top style attribute
        ending_top: '1rem', // Ending top style attribute
        ready: function() { $('.close-reveal-modal:visible').parents().focus(); }, // Callback for Modal open
      });
      // close x's
      $('.close-reveal-modal').click(function(){
        $('#' + $(this).parents().attr('id')).closeModal();
        $('[href=#' + $(this).parents().attr('id') + ']').focus();
      });
      $('.close-reveal-side-nav').click(function(){
        $('[data-activates=' + Drupal.settings.activeSideNav + ']').focus().sideNav('hide');
        setTimeout(function() {
          $('#' + Drupal.settings.activeSideNav).addClass('elmsln-modal-hidden');
          Drupal.settings.activeSideNav = null;
        }, 500);
      });
    }
  };
  // add support for accessibility of materialized components
  $(document).bind('keydown', function(event) {
    if (event.keyCode == 27) {
      // try closing all lightboxes
      var lightboxes = $('.lightbox--is-open .imagelightbox__close').trigger('click');
      if (lightboxes.length == 0) {
        var modals = $('.close-reveal-modal:visible').trigger('click');
        // test that there were modals to close, this allows us to do multiple escapes
        if (modals.length == 0) {
          $('#' + Drupal.settings.activeSideNav + ' .close-reveal-side-nav').trigger('click');
        }
      }
    }
  });
  $(document).ready(function(){
    // remove tab index from lightbox link
    $('[href="javascript:;"]').attr('tabindex','-1');
  });
})(jQuery);
