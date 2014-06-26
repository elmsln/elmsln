/*jshint strict:true, browser:true, curly:true, eqeqeq:true, expr:true, forin:true, latedef:true, newcap:true, noarg:true, trailing: true, undef:true, unused:true */
/*global Drupal: true, jQuery: true, QUnit:true*/
(function ($, Drupal, drupalSettings, window, document, undefined) {
  "use strict";
  Drupal.tests.responsivePreview = {
    getInfo: function() {
      return {
        name: 'Responsive Preview',
        description: 'Tests for the responsive preview feature.',
        group: 'Core'
      };
    },
    setup: function () {},
    teardown: function () {
      // Close the preview container.
      $('#responsive-preview-close').trigger('click');
    },
    tests: {
      navbarTab: function ($, Drupal, window, document, undefined) {
        return function() {
          QUnit.expect(3);

          // Find the navbar tab.
          var $tab = $('.drupal-navbar .navbar-tab-responsive-preview');
          QUnit.equal($tab.length, 1, Drupal.t('The tab is present.'));

          // Verify the tab dropdown click functionality.
          $tab.find('> .trigger').trigger('click');
          QUnit.ok($tab.hasClass('open'), Drupal.t('The tab dropdown list opens.'));

          // Verify the number of devices in the list.
          var devices = drupalSettings.responsive_preview.devices;
          var count = 0;
          for (var device in devices) {
            if (devices.hasOwnProperty(device)) {
              count++;
            }
          }
          var $devices = $tab.find('.options .device');
          QUnit.equal($devices.length, count, Drupal.t('The correct number of devices are listed.'));
        };
      },
      previewLaunch: function ($, Drupal, window, document, undefined) {
        return function () {
          QUnit.expect(3);

          // Find the navbar tab.
          var $tab = $('.drupal-navbar .navbar-tab-responsive-preview');
          // Verify that the responsive preview container is not been built yet.
          var $container = $('#responsive-preview');
          QUnit.equal($container.length, 0, Drupal.t('The preview container does not exist yet.'));

          // Verify that clicking a device link activates the preview container.
          $tab.find('.options .device').first().trigger('click');
          QUnit.stop();
          window.setTimeout(function () {
            $container = $('#responsive-preview');
            // Verify that the preview container exists.
            QUnit.equal($container.length, 1, Drupal.t('The preview container exists.'));

            // Verify that preview container is active.
            QUnit.ok($container.hasClass('active'), Drupal.t('The preview container is active.'));
            QUnit.start();
          }, 500);
        };
      }
    }
  };
})(jQuery, Drupal, drupalSettings, this, this.document);
