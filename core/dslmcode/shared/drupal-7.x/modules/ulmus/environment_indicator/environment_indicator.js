(function ($) {

  Drupal.behaviors.environment_indicatorToolbar = {
    attach: function (context, settings) {
      if (typeof(Drupal.settings.environment_indicator) != 'undefined' && typeof(Drupal.settings.environment_indicator['toolbar-color']) != 'undefined') {
        var environment_name = Drupal.settings.environment_indicator['environment-indicator-name'],
          environment_color = Drupal.settings.environment_indicator['toolbar-color'],
          environment_text_color = Drupal.settings.environment_indicator['toolbar-text-color'],
          $name = $('<div>').addClass('environment-indicator-name-wrapper').html(environment_name);
        $('#toolbar div.toolbar-menu', context).once('environment_indicator').prepend($name);
        $('#toolbar div.toolbar-menu', context).css('background-color', environment_color);
        $('#toolbar div.toolbar-menu .item-list', context).css('background-color', changeColor(environment_color, 0.15, true));
        $('#toolbar div.toolbar-menu ul li:not(.environment-switcher) a', context).css('background-color', environment_color).css('color', environment_text_color);
        $('#toolbar div.toolbar-drawer', context).css('background-color', changeColor(environment_color, 0.25)).find('ul li a').css('color', changeColor(environment_text_color, 0.25));
        $('#toolbar div.toolbar-menu ul li a', context).hover(function () {
          $(this).css('background-color', changeColor(environment_color, 0.1)).css('color', changeColor(environment_text_color, 0.1));
        }, function () {
          $(this).css('background-color', environment_color).css('color', environment_text_color);
          $('#toolbar div.toolbar-menu ul li.active-trail a', context).css('background-color', changeColor(environment_color, 0.1)).css('color', changeColor(environment_text_color, 0.1));
        });
        $('#toolbar div.toolbar-menu ul li.active-trail a', context).css('background-image', 'none').css('background-color', changeColor(environment_color, 0.1)).css('color', changeColor(environment_text_color, 0.1));
        $('#toolbar div.toolbar-drawer ul li a', context).hover(function () {
          $(this).css('background-color', changeColor(environment_color, 0.1, true)).css('color', changeColor(environment_text_color, 0.1, true));
        }, function () {
          $(this).css('background-color', changeColor(environment_color, 0.25)).css('color', changeColor(environment_text_color, 0.25));
          $('#toolbar div.toolbar-drawer ul li.active-trail a', context).css('background-color', changeColor(environment_color, 0.1, true)).css('color', changeColor(environment_text_color, 0.1, true));
        });
        $('#toolbar div.toolbar-drawer ul li.active-trail a', context).css('background-image', 'none').css('background-color', changeColor(environment_color, 0.1, true)).css('color', changeColor(environment_text_color, 0.1, true));
        // Move switcher bar to the top
        var $switcher = $('#toolbar .environment-switcher-container').parent().clone();
        $('#toolbar .environment-switcher-container').parent().remove();
        $('#toolbar').prepend($switcher);
      };
    }
  };

  Drupal.behaviors.environment_indicatorTinycon = {
    attach: function (context, settings) {
      if (typeof(Drupal.settings.environment_indicator) != 'undefined' &&
          typeof(Drupal.settings.environment_indicator.addFavicon) != 'undefined' &&
          Drupal.settings.environment_indicator.addFavicon) {
        //Draw favicon label
        Tinycon.setBubble(Drupal.settings.environment_indicator.faviconLabel);
        Tinycon.setOptions({
          background: Drupal.settings.environment_indicator.faviconColor,
          colour: Drupal.settings.environment_indicator.faviconTextColor
        });
      }
    }
  }

  Drupal.behaviors.environment_indicatorAdminMenu = {
    attach: function (context, settings) {
      if (typeof(Drupal.admin) != 'undefined' && typeof(Drupal.settings.environment_indicator) != 'undefined' && typeof(Drupal.settings.environment_indicator['toolbar-color']) != 'undefined') {
        // Add the restyling behavior to the admin menu behaviors.
        Drupal.admin.behaviors['environment_indicator'] = function (context, settings) {
          $('#admin-menu, #admin-menu-wrapper', context).css('background-color', Drupal.settings.environment_indicator['toolbar-color']);
          $('#admin-menu, #admin-menu-wrapper > ul > li:not(.admin-menu-account) > a', context).css('color', Drupal.settings.environment_indicator['toolbar-text-color']);
          $('#admin-menu .item-list', context).css('background-color', changeColor(Drupal.settings.environment_indicator['toolbar-color'], 0.15, true));
          $('#admin-menu .item-list ul li:not(.environment-switcher) a', context).css('background-color', Drupal.settings.environment_indicator['toolbar-color']).css('color', Drupal.settings.environment_indicator['toolbar-text-color']);
        };
      };
    }
  };

  Drupal.behaviors.environment_indicatorSwitcher = {
    attach: function (context, settings) {
      // Check that the links actually point to the current path, if not, fix them
      $('.environment-switcher a', context).live('click', function (e) {
        e.preventDefault();
        var current_location = window.location;
        window.location.href = current_location.protocol + '//' + e.currentTarget.hostname + current_location.pathname + current_location.search + current_location.hash;
      });
      $('#environment-indicator .environment-indicator-name, #toolbar .environment-indicator-name-wrapper', context).live('click', function () {
        $('#environment-indicator .item-list, #toolbar .item-list', context).slideToggle('fast');
      });
      $('#environment-indicator.position-top.fixed-yes').once(function () {
        $('body').css('margin-top', $('#environment-indicator.position-top.fixed-yes').height() + 'px');
      });
      $('#environment-indicator.position-bottom.fixed-yes').once(function () {
        $('body').css('margin-bottom', $('#environment-indicator.position-bottom.fixed-yes').height() + 'px');
      });
    }
  }

  Drupal.behaviors.environment_indicator_admin = {
    attach: function() {
      // Add the farbtastic tie-in
      if ($.isFunction($.farbtastic) && $('#environment-indicator-color-picker').length > 0) {
        Drupal.settings.environment_indicator_color_picker = $('#environment-indicator-color-picker').farbtastic('#ctools-export-ui-edit-item-form #edit-color');
        Drupal.settings.environment_indicator_text_color_picker = $('#environment-indicator-text-color-picker').farbtastic('#ctools-export-ui-edit-item-form #edit-text-color');
      };
    }
  }


})(jQuery);
