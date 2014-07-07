(function ($) {

  Drupal.behaviors.environment_indicatorToolbar = {
    attach: function (context, settings) {
      if (typeof(settings.environment_indicator) != 'undefined' && typeof(settings.environment_indicator['toolbar-color']) != 'undefined') {
        var environment_name = settings.environment_indicator['environment-indicator-name'],
          environment_color = settings.environment_indicator['toolbar-color'],
          environment_text_color = settings.environment_indicator['toolbar-text-color'],
          $name = $('<div>').addClass('environment-indicator-name-wrapper').html(environment_name),
          $toolbar = $('#toolbar, #navbar-bar', context);
        $('div.toolbar-menu', $toolbar).once('environment_indicator').prepend($name);
        $('div.toolbar-menu', $toolbar).css('background-color', environment_color);
        $('div.toolbar-menu .item-list', $toolbar).css('background-color', changeColor(environment_color, 0.15, true));
        $('div.toolbar-menu ul li:not(.environment-switcher) a', $toolbar).css('background-color', environment_color).css('color', environment_text_color);
        $('div.toolbar-drawer', $toolbar).css('background-color', changeColor(environment_color, 0.25)).find('ul li a').css('color', changeColor(environment_text_color, 0.25));
        $('div.toolbar-menu ul li a', $toolbar).hover(function () {
          $(this).css('background-color', changeColor(environment_color, 0.1)).css('color', changeColor(environment_text_color, 0.1));
        }, function () {
          $(this).css('background-color', environment_color).css('color', environment_text_color);
          $('div.toolbar-menu ul li.active-trail a', $toolbar).css('background-color', changeColor(environment_color, 0.1)).css('color', changeColor(environment_text_color, 0.1));
        });
        $('div.toolbar-menu ul li.active-trail a', $toolbar).css('background-image', 'none').css('background-color', changeColor(environment_color, 0.1)).css('color', changeColor(environment_text_color, 0.1));
        $('div.toolbar-drawer ul li a', $toolbar).hover(function () {
          $(this).css('background-color', changeColor(environment_color, 0.1, true)).css('color', changeColor(environment_text_color, 0.1, true));
        }, function () {
          $(this).css('background-color', changeColor(environment_color, 0.25)).css('color', changeColor(environment_text_color, 0.25));
          $('div.toolbar-drawer ul li.active-trail a', $toolbar).css('background-color', changeColor(environment_color, 0.1, true)).css('color', changeColor(environment_text_color, 0.1, true));
        });
        $('div.toolbar-drawer ul li.active-trail a', $toolbar).css('background-image', 'none').css('background-color', changeColor(environment_color, 0.1, true)).css('color', changeColor(environment_text_color, 0.1, true));
        // Move switcher bar to the top
        var $switcher_container = $('.environment-switcher-container', $toolbar);
        var $switcher = $switcher_container.parent().clone();
        $switcher_container.parent().remove();
        $toolbar.prepend($switcher);
        // Add a margin if the Shortcut module toggle button is present.
        if ($('div.toolbar-menu a.toggle', $toolbar).length > 0) {
          $('div.toolbar-menu', $toolbar).css('padding-right', 40);
        }
      };
    }
  };

  Drupal.behaviors.environment_indicatorTinycon = {
    attach: function (context, settings) {
      if (typeof(settings.environment_indicator) != 'undefined' &&
          typeof(settings.environment_indicator.addFavicon) != 'undefined' &&
          settings.environment_indicator.addFavicon) {
        //Draw favicon label
        Tinycon.setBubble(settings.environment_indicator.faviconLabel);
        Tinycon.setOptions({
          background: settings.environment_indicator.faviconColor,
          colour: settings.environment_indicator.faviconTextColor
        });
      }
    }
  }

  Drupal.behaviors.environment_indicatorAdminMenu = {
    attach: function (context, settings) {
      if (typeof(Drupal.admin) != 'undefined' && typeof(settings.environment_indicator) != 'undefined' && typeof(settings.environment_indicator['toolbar-color']) != 'undefined') {
        // Add the restyling behavior to the admin menu behaviors.
        Drupal.admin.behaviors['environment_indicator'] = function (context, settings) {
          $('#admin-menu, #admin-menu-wrapper', context).css('background-color', settings.environment_indicator['toolbar-color']);
          $('#admin-menu, #admin-menu-wrapper > ul > li:not(.admin-menu-account) > a', context).css('color', settings.environment_indicator['toolbar-text-color']);
          $('#admin-menu .item-list', context).css('background-color', changeColor(settings.environment_indicator['toolbar-color'], 0.15, true));
          $('#admin-menu .item-list ul li:not(.environment-switcher) a', context).css('background-color', settings.environment_indicator['toolbar-color']).css('color', settings.environment_indicator['toolbar-text-color']);
        };
      };
    }
  };

  Drupal.behaviors.environment_indicatorNavbar = {
    attach: function (context, settings) {
      if (typeof(settings.navbar) != 'undefined' && typeof(settings.environment_indicator) != 'undefined' && typeof(settings.environment_indicator['toolbar-color']) != 'undefined') {
        $('#navbar-administration .navbar-bar', context).css('background-color', settings.environment_indicator['toolbar-color']);
        $('#navbar-administration .navbar-tab *:not(select)', context).css('color', settings.environment_indicator['toolbar-text-color']);
      }
    }
  };

  Drupal.behaviors.environment_indicatorSwitcher = {
    attach: function (context, settings) {
      // Check that the links actually point to the current path, if not, fix them
      $('.environment-switcher a', context).click(function (e) {
        e.preventDefault();
        var current_location = window.location;
        window.location.href = current_location.protocol + '//' + e.currentTarget.hostname + current_location.pathname + current_location.search + current_location.hash;
      });
      $('#environment-indicator .environment-indicator-name, #toolbar .environment-indicator-name-wrapper, #navbar-bar .environment-indicator-name-wrapper', context).click(function () {
        $('#environment-indicator .item-list, #toolbar .item-list, #navbar-bar .item-list', context).slideToggle('fast');
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
    attach: function(context, settings) {
      var $picker = $('#environment-indicator-color-picker');
      // Add the farbtastic tie-in
      if ($.isFunction($.farbtastic) && $picker.length > 0) {
        settings.environment_indicator_color_picker = $picker.farbtastic('#ctools-export-ui-edit-item-form #edit-color');
        settings.environment_indicator_text_color_picker = $('#environment-indicator-text-color-picker').farbtastic('#ctools-export-ui-edit-item-form #edit-text-color');
      }
    }
  }

})(jQuery);
