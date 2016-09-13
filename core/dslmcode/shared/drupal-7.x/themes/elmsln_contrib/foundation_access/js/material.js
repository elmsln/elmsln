(function($) {
'use strict';
  // Add wave effect.
  Drupal.behaviors.foundation_access_waves = {
    attach: function (context, settings) {
      var waveEffect = "waves-effect waves-orange";
      // MOOC
      $(".mooc-helper-toc, #block-mooc-helper-mooc-helper-toc-nav-modal a, .book-sibling-nav-container li").addClass(waveEffect);
      // GENERIC
      $("button").addClass(waveEffect);
      // DROPDOWNS
      $("#r-header__icon--advanced li, #courseToolsMenu li").addClass(waveEffect);
      // TABS
      $(".horizontal-tabs-list .horizontal-tab-button").addClass(waveEffect);
      // LMSLESS
      $("#block-cis-lmsless-cis-lmsless-network-nav-modal a, .elmsln-network-button, .elmsln-user-button, .elmsln-syllabus-button, .elmsln-resource-button, .elmsln-help-button").addClass(waveEffect);
      // INPAGE WIDGET
      //$(".cis-filter-activity-item").addClass("waves-effect waves-button waves-classic");
      $(".cis-filter-activity-item ul.submit-widget-links li").addClass(waveEffect);
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
      $('.carousel-slider').carousel({full_width: true});
    }
  };
})(jQuery);
