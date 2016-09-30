(function($) {
'use strict';
  // Add wave effect.
  Drupal.behaviors.foundation_access_waves = {
    attach: function (context, settings) {
      var waveEffect = "waves-effect waves-orange";
      // MOOC
      $("#block-mooc-helper-mooc-helper-toc-nav-modal a, .book-sibling-nav-container li").addClass(waveEffect);
      // GENERIC
      $("button").addClass(waveEffect);
      // DROPDOWNS
      $("#r-header__icon--advanced li, #courseToolsMenu li").addClass(waveEffect);
      // TABS
      $(".horizontal-tabs-list .horizontal-tab-button").addClass(waveEffect);
      // IN PAGE MENU
      $(".header-menu-options li, .elmsln-home-button-link").addClass(waveEffect);
    }
  };
  Drupal.behaviors.wavesInit = {
    attach: function (context, settings) {
        Waves.displayEffect();
    }
  };
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
      $('.elmsln-right-side-nav-trigger').sideNav({
        menuWidth: 400, // Default is 240
        edge: 'right', // Choose the horizontal origin
        closeOnClick: false // Closes side-nav on <a> clicks, useful for Angular/Meteor
      });
      $('.elmsln-left-side-nav-trigger').sideNav({
        menuWidth: 280, // Default is 240
        edge: 'left', // Choose the horizontal origin
        closeOnClick: false // Closes side-nav on <a> clicks, useful for Angular/Meteor
      });
      $('.elmsln-modal-trigger').leanModal({
        dismissible: true, // Modal can be dismissed by clicking outside of the modal
        opacity: .5, // Opacity of modal background
        in_duration: 150, // Transition in duration
        out_duration: 150, // Transition out duration
        starting_top: '1rem', // Starting top style attribute
        ending_top: '1rem', // Ending top style attribute
      });
      // close x's
      $('.close-reveal-modal').click(function(){
        $('#' + $(this).parents().attr('id')).closeModal();
      });
      $('.close-reveal-side-nav').click(function(){
        $('[data-activates=' + $(this).parents().attr('id') + ']').sideNav('hide');
      });
    }
  };
  $(document).bind('keydown', function(event) {
    if (event.keyCode == 27) {
      $("body").removeClass("scroll-disabled")
      if ( typeof Drupal.settings.entity_iframe !== "undefined" && typeof Drupal.settings.entity_iframe.autoClose !== "undefined") {
        location.reload();
      }
      return false;
    }
  });
})(jQuery);
