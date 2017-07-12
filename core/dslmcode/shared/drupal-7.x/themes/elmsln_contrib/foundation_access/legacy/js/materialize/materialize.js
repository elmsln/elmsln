(function($) {
'use strict';
  /**
   * behavior to make sure select lists are applied every time we do an ajax reload.
   */
  Drupal.behaviors.materializeCSS = {
    attach: function (context, settings) {
      // select lists but not the chosen ones
      $('select').not('.chosen').not('.cke_dialog_body select').not('.form-select.initialized').material_select();
    }
  };

  Drupal.settings.activeSideNav = null;
  // add support for accessibility of materialized components
  $(document).bind('keydown', function(event) {
    if (event.keyCode == 27) {
      $('.elmsln-dropdown-button.active').dropdown('close');
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
  // events that help with teeing up materialize styles the first run
  $(document).ready(function(){
    // enable parallax
    $('.parallax').parallax();
    // normal carousel
    $('.carousel').not('.carousel-slider').carousel();
    // full size slider carousel
    $('.carousel-slider').carousel({full_width: true});
    // collapsible sets
    $('.collapsible').collapsible({
      accordion : false // A setting that changes the collapsible behavior to expandable instead of the default accordion style
    });
    // dropdown items
    $('.elmsln-dropdown-button').dropdown({
      inDuration: 150,
      outDuration: 50,
      constrain_width: false,
      hover: false,
      gutter: 0,
      belowOrigin: true,
      alignment: 'left'
    });
    $('body:not(.page-cle-app) .elmsln-dropdown-button').click(function(){
      $('#etb-course-nav').css('z-index', '2');
    });
    // side triggers
    $('.elmsln-right-side-nav-trigger').bind('click', function() {
        $('#' + $(this).attr('data-activates')).removeClass('elmsln-modal-hidden').focus();
        Drupal.settings.activeSideNav = $(this).attr('data-activates');
      }).sideNav({
      menuWidth: 400, // Default is 240
      edge: 'right',
      closeOnClick: false
    });
    $('.elmsln-right-side-nav-widget-trigger').bind('click', function() {
        $('#' + $(this).attr('data-activates')).removeClass('elmsln-modal-hidden').focus();
        Drupal.settings.activeSideNav = $(this).attr('data-activates');
      }).sideNav({
      menuWidth: '50%',
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
    // modal items
    $('.elmsln-modal-trigger').bind('click', function() {
      // hide all currently visible modals
      $('.close-reveal-modal:visible').trigger('click');
    });
    $('.elmsln-modal').modal({
      dismissible: true, // Modal can be dismissed by clicking outside of the modal
      opacity: .5, // Opacity of modal background
      in_duration: 150, // Transition in duration
      out_duration: 50, // Transition out duration
      starting_top: '8rem', // Starting top style attribute
      ending_top: '8rem', // Ending top style attribute
      ready: function(modal, trigger) {
        $('.close-reveal-modal:visible').parents().focus();
      }, // Callback for Modal open
    });
    // close x's for modals
    $('.close-reveal-modal').click(function(){
      $('#' + $(this).parents().parents().attr('id')).modal('close');
      $('[href=#' + $(this).parents().attr('id') + '] paper-button').focus();
    });
    // close x's for the side-nav items
    $('.close-reveal-side-nav').click(function(){
      $('[data-activates=' + Drupal.settings.activeSideNav + '] paper-button').focus().sideNav('hide');
      setTimeout(function() {
        $('#' + Drupal.settings.activeSideNav).addClass('elmsln-modal-hidden');
        Drupal.settings.activeSideNav = null;
      }, 150);
    });
  });
})(jQuery);
