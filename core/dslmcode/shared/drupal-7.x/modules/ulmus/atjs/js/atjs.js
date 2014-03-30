(function($) {
  var drupal_atjs = drupal_atjs || {};
  $(document).ready(function(){
    drupal_atjs.ckeditor();
    drupal_atjs.tinymce();
  });
  Drupal.behaviors.atjs = {
    attach: function(context, settings) {
      drupal_atjs['storage'] = {};
      if (Drupal.wysiwyg !== undefined) {
        $.each(Drupal.wysiwyg.editor.init, function(editor) {
          if (typeof drupal_atjs[editor] == 'function') {
            drupal_atjs[editor](context);
          }
        });
      }
      else if (Drupal.settings.ckeditor !== undefined) {
        drupal_atjs.ckeditor(context);
      }

      $.each(Drupal.settings.atjs, function(element, listeners) {
        if ($('#' + element + '.atjs').length && !$('#' + element).hasClass('atjs-processed')) {
          drupal_atjs.processListeners(element, element, context, false);

          $('#' + element).addClass('atjs-processed');
        }
      });
    }
  };

  drupal_atjs.processListeners = function(element, element_target, context, content_editable) {
    if ($('#' + element + '.atjs').length) {
      $.each(Drupal.settings.atjs[element], function(listener_name, listener) {
        listener['callbacks'] = {};
        listener['callbacks']['remote_filter'] = function(query, callback) {
          var key = query;

          if (key.length >= 1) {
            if (typeof drupal_atjs['storage'][listener_name + '::' + key] === 'undefined') {
              $.get(Drupal.settings.basePath + '?q=atjs/ajax/' + listener_name + '/' + key, function(response) {
                drupal_atjs['storage'][listener_name + '::' + key] = response;
                callback(response);
              });
            }
            else {
              callback(drupal_atjs['storage'][listener_name + '::' + key]);
            }
          }
        };

        if (content_editable) {
          $(element_target, context).atwho(listener);
        }
        else {
          $('#' + element_target, context).atwho(listener);
        }
      });
    }
  };

  /**
   * Integrate with ckEditor.
   */
  drupal_atjs.ckeditor = function(context) {
    var onlyOnce = false;
    if (!onlyOnce && typeof CKEDITOR == 'object') {
      onlyOnce = true;
      CKEDITOR.on('instanceReady', function(e) {
        var editor = $('#' + e.editor.name + '.atjs');
        if (editor.length == 1) {
          drupal_atjs.processListeners(e.editor.name, e.editor.document.$.body, context, true);
        }
      });
    }
  };

  /**
   * Integrate with TinyMCE.
   */
  drupal_atjs.tinymce = function(context) {
    var onlyOnce = false;
    if (!onlyOnce && typeof tinyMCE == 'object') {
      onlyOnce = true;
      tinyMCE.onAddEditor.add(function(mgr, ed) {
        var editor = $('#' + ed.editorId + '.atjs');
        if (editor.length == 1) {
          ed.onInit.add(function(ed, l) {
            drupal_atjs.processListeners(ed.editorId, ed.contentDocument.activeElement, context, true);
          });
        }
      });
    }
  };

})(jQuery);
