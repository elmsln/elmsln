/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true, QUnit:true*/
(function ($, Drupal, drupalSettings, window, document, undefined) {
  "use strict";
  Drupal.tests.responsivePreviewAdmin = {
    getInfo: function() {
      return {
        name: 'Responsive Preview',
        description: 'Tests for the responsive preview admin.',
        group: 'Core'
      };
    },
    setup: function () {},
    teardown: function () {},
    tests: {
      navbarTab: function ($, Drupal, window, document, undefined) {
        return function() {
          QUnit.expect(1);

          // The navbar tab should not be present on an admin path.
          var $tab = $('.drupal-navbar .navbar-tab-responsive-preview');
          QUnit.equal($tab.length, 0, Drupal.t('The tab is not present.'));
        };
      }
    }
  };
})(jQuery, Drupal, drupalSettings, this, this.document);
