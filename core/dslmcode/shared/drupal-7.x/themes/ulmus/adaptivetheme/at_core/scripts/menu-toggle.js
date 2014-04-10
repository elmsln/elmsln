(function ($) {
  Drupal.behaviors.ATmenuToggle = {
    attach: function (context, settings) {

      if ($.browser.msie && parseFloat($.browser.version) <= 8) {
        return;
      }

      var activeTheme = Drupal.settings["ajaxPageState"]["theme"];
      var themeSettings = Drupal.settings['adaptivetheme'];

      if (typeof themeSettings[activeTheme] == 'undefined') {
        return;
      }

      var mtsTP = themeSettings[activeTheme]['menu_toggle_settings']['tablet_portrait'];
      var mtsTL = themeSettings[activeTheme]['menu_toggle_settings']['tablet_landscape'];

      var breakpoints = {
        bp1: themeSettings[activeTheme]['media_query_settings']['smalltouch_portrait'],
        bp2: themeSettings[activeTheme]['media_query_settings']['smalltouch_landscape'],
      };

      if (mtsTP == 'true') { breakpoints.push(bp3 + ':' + themeSettings[activeTheme]['media_query_settings']['tablet_portrait']); }
      if (mtsTL == 'true') { breakpoints.push(bp4 + ':' + themeSettings[activeTheme]['media_query_settings']['tablet_portrait']); }

      $(".at-menu-toggle h2", context).removeClass('element-invisible').addClass('at-menu-toggle-button').wrapInner('<a href="#menu-toggle" class="at-menu-toggle-button-link" />');
      $(".at-menu-toggle ul[class*=menu]:nth-of-type(1)", context).wrap('<div class="menu-toggle" />');

      !function(breakName, query){
        // Run the callback on current viewport
        cb({
          media: query,
          matches: matchMedia(query).matches
        });
        // Subscribe to breakpoint changes
        matchMedia(query).addListener(cb);
      }(name, breakpoints[name]);

      // Callback
      function cb(data){
      	// Toggle menus open or closed
      	$(".at-menu-toggle-button-link", context).click(function() {
          $(this).parent().siblings('.menu-toggle').slideToggle(100, 'swing').toggleClass('menu-toggle-open');
          return false;
        });

        /*
        // Close if clicked outside (inc another toggle menu)
        $(".at-menu-toggle-button-link", context).bind('clickoutside', function(event) {
          $(this).parent().siblings('.menu-toggle').slideUp(100, 'swing').removeClass('menu-toggle-open');
          //return false;
        });
        */
      }

      //console.log(themeSettings);
    }
  };
})(jQuery);
