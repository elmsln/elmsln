/* global CSSCriticalPath: true */
(function(w, d, $) {
  'use strict';

  Drupal.behaviors.criticalCss = {
    attach: function(context, settings) {

      var $button = $('#css-delivery-builder-wrapper > .do-build');

      $('body').once('css-delivery-builder');

      $button.once('critical-css').click(function() {
        w.scrollTo(0, 0);
        $(this).attr('disabled', 'disabled');
        Drupal.criticalCss.updateStatus(Drupal.t('CSS is being generated...'));

        setTimeout(function() {
          Drupal.criticalCss.parse(settings.criticalCss);
        }, 0);
      });

      if ($button.length) {
        Drupal.criticalCss.updateStatus(Drupal.t('Ready to build.'));
      }
    }
  };

  Drupal.criticalCss = {

    css: null,

    parse: function(options) {
      var parser = new CSSCriticalPath(w, d, options);
      this.css = parser.generateCSS();
      $('#css-delivery-builder-wrapper > .do-build').attr('disabled', '');
      Drupal.criticalCss.updateStatus(Drupal.t('Done. <a class="postback-link" href="#save" data-op="save">Save</a> the generated critical CSS in configuration or alternatively <a class="postback-link" href="#download" data-op="download">Download</a> the generated critical CSS to a file.'));

      $('.postback-link').click(function(e) {
        var op = $(this).data('op');
        Drupal.criticalCss.postBack(op);
        e.preventDefault();
      });

    },

    updateStatus: function(msg) {
      $('#css-delivery-builder-wrapper > .build-result').html(msg);
    },

    postBack: function(op) {
      if (this.css.length > 0) {
        $.ajax({
          type: 'POST',
          url: Drupal.settings.basePath + 'css_delivery/postback',
          data: {
            op: op,
            css: encodeURI(this.css)
          },
          success: function(response, status, xhr) {
            if (op === 'save' && response.status === 'ok') {
              Drupal.criticalCss.updateStatus(response.message);
            }
            else {
              // check for a filename
              var filename = '';
              var disposition = xhr.getResponseHeader('Content-Disposition');
              if (disposition && disposition.indexOf('attachment') !== -1) {
                var filenameRegex = /filename[^;=\n]*=((['"]).*?\2|[^;\n]*)/;
                var matches = filenameRegex.exec(disposition);
                if (matches !== null && matches[1]) {
                  filename = matches[1].replace(/['"]/g, '');
                }
              }

              var type = xhr.getResponseHeader('Content-Type');
              var blob = new Blob([response], { type: type });

              if (typeof window.navigator.msSaveBlob !== 'undefined') {
                // IE workaround for "HTML7007: One or more blob URLs were revoked by closing the blob for which they were created. These URLs will no longer resolve as the data backing the URL has been freed."
                window.navigator.msSaveBlob(blob, filename);
              }
              else {
                var URL = window.URL || window.webkitURL;
                var downloadUrl = URL.createObjectURL(blob);

                if (filename) {
                  // use HTML5 a[download] attribute to specify filename
                  var a = document.createElement('a');
                  // safari doesn't support this yet
                  if (typeof a.download === 'undefined') {
                      window.location = downloadUrl;
                  } else {
                      a.href = downloadUrl;
                      a.download = filename;
                      document.body.appendChild(a);
                      a.click();
                  }
                }
                else {
                  window.location = downloadUrl;
                }
                setTimeout(function() {
                  URL.revokeObjectURL(downloadUrl);
                }, 100);
              }
            }
          }
        });
      }
    }

  };


}(window, document, jQuery));
