/* global jQuery:false */
/* global Drupal:false */
/* global JSHINT:false */
/* global CSSLint:false */

/**
 * @file
 * Run JSHINT in the browser against the servers JS.
 */

/**
 * Have clicks to advagg_validator_js classes run JSHINT clientside.
 */
(function ($) {
  "use strict";
  Drupal.behaviors.advagg_validator_js_simple = {
    attach: function (context, settings) {
      $('.advagg_validator_js', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).siblings('.filenames'), function() {
          var filename = $(this).val();
          if (filename) {
            try {
              var t = new Date().getTime();
              var x = jQuery.ajax({
                url: settings.basePath + filename + '?t=' + t,
                dataType: 'text',
                async: false
              });
              if (JSHINT(x.responseText, Drupal.settings.jshint, Drupal.settings.jshint.predef)) {
                $(results).append('<h4>' + filename + ' Passed!</h4>');
              } else {
                $(results).append('<p><h4>' + filename + ' Failed!</h4>');
                $(results).append('<ul>');
                for (var i = 0; i < JSHINT.errors.length; i++) {
                  $(results).append('<li><b>' + JSHINT.errors[i].line + ':</b> ' + JSHINT.errors[i].reason + '</li>');
                }
                $(results).append('</ul></p>');
              }
            }
            catch (err) {
              $(results).append(err);
            }
          }
        });

        return false;
      });
    }
  };
}(jQuery));

/**
 * Have clicks to advagg_validator_recursive_js classes run JSHINT clientside.
 */
(function ($) {
  "use strict";
  Drupal.behaviors.advagg_validator_js_recursive = {
    attach: function (context, settings) {
      $('.advagg_validator_recursive_js', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).parent().find('.filenames'), function() {
          var filename = $(this).val();
          if (filename) {
            try {
              var t = new Date().getTime();
              var x = jQuery.ajax({
                url: settings.basePath + filename + '?t=' + t,
                dataType: 'text',
                async: false
              });
              if (JSHINT(x.responseText, Drupal.settings.jshint, Drupal.settings.jshint.predef)) {
                $(results).append('<h4>' + filename + ' Passed!</h4>');
              } else {
                $(results).append('<p><h4>' + filename + ' Failed!</h4>');
                $(results).append('<ul>');
                for (var i = 0; i < JSHINT.errors.length; i++) {
                  $(results).append('<li><b>' + JSHINT.errors[i].line + ':</b> ' + JSHINT.errors[i].reason + '</li>');
                }
                $(results).append('</ul></p>');
              }
            }
            catch (err) {
              $(results).append(err);
            }
          }
        });

        return false;
      });
    }
  };
}(jQuery));

/**
 * Have clicks to advagg_validator_css classes run CSSLint clientside.
 */
(function ($) {
  "use strict";
  Drupal.behaviors.advagg_validator_css_simple = {
    attach: function (context, settings) {
      $('.advagg_validator_css', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).siblings('.filenames'), function() {
          var filename = $(this).val();
          if (filename) {
            try {
              var t = new Date().getTime();
              var x = jQuery.ajax({
                url: settings.basePath + filename + '?t=' + t,
                dataType: 'text',
                async: false
              });

              var y = CSSLint.verify(x.responseText);
              var z = y.messages;
              $(results).append('<p><h4>' + filename + '</h4>');
              $(results).append('<ul>');
              for (var i=0, len=z.length; i < len; i++) {
                var w = z[i].message + ' (line ' + z[i].line + ', col ' + z[i].col + ')';
                $(results).append('<li class="' + z[i].type + '">' + w.replace(/ /g, '&nbsp;') + '</li>');
              }
              $(results).append('</ul></p>');
            }
            catch (err) {
              $(results).append(err);
            }
          }
        });

        return false;
      });
    }
  };
}(jQuery));

/**
 * Have clicks to advagg_validator_recursive_css classes run CSSLint clientside.
 */
(function ($) {
  "use strict";
  Drupal.behaviors.advagg_validator_css_recursive = {
    attach: function (context, settings) {
      $('.advagg_validator_recursive_css', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).parent().find('.filenames'), function() {
          var filename = $(this).val();
          if (filename) {
            try {
              var t = new Date().getTime();
              var x = jQuery.ajax({
                url: settings.basePath + filename + '?t=' + t,
                dataType: 'text',
                async: false
              });

              var y = CSSLint.verify(x.responseText);
              var z = y.messages;
              $(results).append('<p><h4>' + filename + '</h4>');
              $(results).append('<ul>');
              for (var i=0, len=z.length; i < len; i++) {
                var w = z[i].message + ' (line ' + z[i].line + ', col ' + z[i].col + ')';
                $(results).append('<li class="' + z[i].type + '">' + w.replace(/ /g, '&nbsp;') + '</li>');
              }
              $(results).append('</ul></p>');
            }
            catch (err) {
              $(results).append(err);
            }
          }
        });

        return false;
      });
    }
  };
}(jQuery));
