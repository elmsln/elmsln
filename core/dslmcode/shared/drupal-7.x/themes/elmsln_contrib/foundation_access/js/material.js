(function($) {
'use strict';
// Add wave effect.
Drupal.behaviors.foundation_access_waves = {
  attach: function (context, settings) {
    // MOOC
    $(".mooc-helper-toc").addClass("waves-effect waves-button waves-classic");
    $("#block-mooc-helper-mooc-helper-toc-nav-modal a").addClass("waves-effect waves-button waves-classic");
    $(".book-sibling-nav-container li").addClass("waves-effect waves-button waves-classic");
    // GENERIC
    $("button").addClass("waves-effect waves-button waves-classic");
    // DROPDOWNS
    $("#r-header__icon--advanced li, #courseToolsMenu li").addClass("waves-button waves-classic");
    // TABS
    $(".horizontal-tabs-list .horizontal-tab-button").addClass("waves-effect waves-button waves-classic");
    // LMSLESS
    $(".top-bar.etb-nav ul.left li.apps").addClass("waves-effect waves-classic");
    $("#block-cis-lmsless-cis-lmsless-network-nav-modal a").addClass("waves-effect waves-button waves-classic");
    // INPAGE WIDGET
    //$(".cis-filter-activity-item").addClass("waves-effect waves-button waves-classic");
    // IN PAGE MENU
    $(".header-menu-options li").addClass("waves-effect waves-classic");
    $(".elmsln-home-button-link").addClass("waves-effect waves-button waves-classic");
    // submit widget
    $(".cis-filter-activity-item ul.submit-widget-links li").addClass("waves-effect waves-button waves-classic waves-float");
  }
};
  Drupal.behaviors.wavesInit = {
    attach: function (context, settings) {
        Waves.displayEffect();
    }
  };
  Drupal.behaviors.materialSelect = {
    attach: function(context) {
      $('select').material_select();
    }
  };
})(jQuery);
