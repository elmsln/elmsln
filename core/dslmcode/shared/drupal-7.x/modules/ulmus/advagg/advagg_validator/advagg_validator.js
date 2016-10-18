/**
 * @file
 * Run JSHINT in the browser against the servers JS.
 */

/* global jQuery:false */
/* global Drupal:false */
/* global JSHINT:false */
/* global CSSLint:false */

/**
 * Have clicks to advagg_validator_js classes run JSHINT clientside.
 */
(function ($) {
  'use strict';
  Drupal.behaviors.advagg_validator_js_simple = {
    attach: function (context, settings) {
      $('.advagg_validator_js', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).siblings('.filenames'), function () {
          var filename = $(this).val();
          if (filename) {
            try {
              var t = new Date().getTime();
              var x = jQuery.ajax({
                url: settings.basePath + filename + '?t=' + t,
                dataType: 'text',
                async: false
              });
              if (!JSHINT(x.responseText, Drupal.settings.jshint, Drupal.settings.jshint.predef)) {
                $(results).append('<p><h4>' + filename + '</h4><ul>');
                for (var i = 0; i < JSHINT.errors.length; i++) {
                  var ignore = (Drupal.settings.jshint && Drupal.settings.jshint.ignore) ? Drupal.settings.jshint.ignore.split(',') : [];
                  if (ignore.indexOf(JSHINT.errors[i].code) === -1) {
                    var w = JSHINT.errors[i].reason + ' (line ' + JSHINT.errors[i].line + ', col ' + JSHINT.errors[i].character + ', rule ' + JSHINT.errors[i].code + ')';
                    $(results).append('<li class="' + JSHINT.errors[i].id.replace(/[()]/g, '') + '">' + w.replace(/ /g, '&nbsp;') + '</li>');
                  }
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
  'use strict';
  Drupal.behaviors.advagg_validator_js_recursive = {
    attach: function (context, settings) {
      $('.advagg_validator_recursive_js', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).parent().find('.filenames'), function () {
          var filename = $(this).val();
          if (filename) {
            try {
              var t = new Date().getTime();
              var x = jQuery.ajax({
                url: settings.basePath + filename + '?t=' + t,
                dataType: 'text',
                async: false
              });
              if (!JSHINT(x.responseText, Drupal.settings.jshint, Drupal.settings.jshint.predef)) {
                $(results).append('<p><h4>' + filename + '</h4><ul>');
                for (var i = 0; i < JSHINT.errors.length; i++) {
                  var ignore = (Drupal.settings.jshint && Drupal.settings.jshint.ignore) ? Drupal.settings.jshint.ignore.split(',') : [];
                  if (ignore.indexOf(JSHINT.errors[i].code) === -1) {
                    var w = JSHINT.errors[i].reason + ' (line ' + JSHINT.errors[i].line + ', col ' + JSHINT.errors[i].character + ', rule ' + JSHINT.errors[i].code + ')';
                    $(results).append('<li class="' + JSHINT.errors[i].id.replace(/[()]/g, '') + '">' + w.replace(/ /g, '&nbsp;') + '</li>');
                  }
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
  'use strict';
  Drupal.behaviors.advagg_validator_css_simple = {
    attach: function (context, settings) {
      $('.advagg_validator_css', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).siblings('.filenames'), function () {
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
              $(results).append('<p><h4>' + filename + '</h4><ul>');
              for (var i = 0, len = z.length; i < len; i++) {
                var ignore = (Drupal.settings.csslint && Drupal.settings.csslint.ignore) ? Drupal.settings.csslint.ignore.split(',') : [];
                if (ignore.indexOf(z[i].rule.id) === -1) {
                  var w = z[i].message + ' (line ' + z[i].line + ', col ' + z[i].col + ', rule ' + z[i].rule.id + ')';
                  $(results).append('<li class="' + z[i].type + '">' + w.replace(/ /g, '&nbsp;') + '</li>');
                }
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
  'use strict';
  Drupal.behaviors.advagg_validator_css_recursive = {
    attach: function (context, settings) {
      $('.advagg_validator_recursive_css', context).click(function (context) {
        // Get Results Div.
        var results = $(this).siblings('.results');
        // Clear out the results.
        $(results).html('');
        // Loop over each filename.
        $.each($(this).parent().find('.filenames'), function () {
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
              $(results).append('<p><h4>' + filename + '</h4><ul>');
              for (var i = 0, len = z.length; i < len; i++) {
                var ignore = (Drupal.settings.csslint && Drupal.settings.csslint.ignore) ? Drupal.settings.csslint.ignore.split(',') : [];
                if (ignore.indexOf(z[i].rule.id) === -1) {
                  var w = z[i].message + ' (line ' + z[i].line + ', col ' + z[i].col + ', rule ' + z[i].rule.id + ')';
                  $(results).append('<li class="' + z[i].type + '">' + w.replace(/ /g, '&nbsp;') + '</li>');
                }
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
