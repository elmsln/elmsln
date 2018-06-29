(function ($) {

/**
 * Initialize editor instances.
 *
 * @see Drupal.wysiwyg.editor.init.ckeditor()
 */
Drupal.wysiwyg.editor.init.tinymce = function (settings, pluginInfo) {
  // Fix Drupal toolbar obscuring editor toolbar in fullscreen mode.
  var $drupalToolbars = $('#toolbar, #admin-menu', Drupal.overlayChild ? window.parent.document : document);
  tinymce.on('AddEditor', function (e) {
    e.editor.on('FullscreenStateChanged', function (e) {
      if (e.state) {
        $drupalToolbars.hide();
      }
      else {
        $drupalToolbars.show();
      }
    });
  });
  // Register new plugins.
  Drupal.wysiwyg.editor.update.tinymce(settings, pluginInfo);
};

/**
 * Update the editor library when new settings are available.
 *
 * @see Drupal.wysiwyg.editor.update.ckeditor()
 */
Drupal.wysiwyg.editor.update.tinymce = function (settings, pluginInfo) {
  // Load native external plugins.
  // Array syntax required; 'native' is a predefined token in JavaScript.
  var plugin;
  for (plugin in pluginInfo['native']) {
    if (!(plugin in tinymce.PluginManager.lookup || plugin in tinymce.PluginManager.urls)) {
      tinymce.PluginManager.load(plugin, pluginInfo['native'][plugin]);
    }
  }
  // Load Drupal plugins.
  for (plugin in pluginInfo.drupal) {
    if (!(plugin in tinymce.PluginManager.lookup)) {
      Drupal.wysiwyg.editor.instance.tinymce.addPlugin(plugin, pluginInfo.drupal[plugin]);
    }
  }
};

/**
 * Attach this editor to a target element.
 *
 * See Drupal.wysiwyg.editor.attach.none() for a full description of this hook.
 */
Drupal.wysiwyg.editor.attach.tinymce = function (context, params, settings) {
  // Remove TinyMCE's internal mceItem class, which was incorrectly added to
  // submitted content by Wysiwyg <2.1. TinyMCE only temporarily adds the class
  // for placeholder elements. If preemptively set, the class prevents (native)
  // editor plugins from gaining an active state, so we have to manually remove
  // it prior to attaching the editor. This is done on the client-side instead
  // of the server-side, as Wysiwyg has no way to figure out where content is
  // stored, and the class only affects editing.
  var $field = $('#' + params.field);
  $field.val($field.val().replace(/(<.+?\s+class=['"][\w\s]*?)\bmceItem\b([\w\s]*?['"].*?>)/ig, '$1$2'));

  // Attach editor.
  settings.selector = '#' + params.field;
  var oldSetup = settings.setup;
  settings.setup = function (editor) {
    editor.on('focus', function (e) {
      Drupal.wysiwyg.activeId = this.id;
    });
    if (oldSetup) {
      oldSetup(editor);
    }
  };
  tinymce.init(settings);
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full description of this hook.
 */
Drupal.wysiwyg.editor.detach.tinymce = function (context, params, trigger) {
  var instance;
  if (typeof params !== 'undefined') {
    instance = tinymce.get(params.field);
    if (instance) {
      instance.save();
      if (trigger !== 'serialize') {
        instance.remove();
      }
    }
  }
  else {
    // Save contents of all editors back into textareas.
    tinymce.triggerSave();
    if (trigger !== 'serialize') {
      // Remove all editor instances.
      for (instance in tinymce.editors) {
        if (!tinymce.editors.hasOwnProperty(instance)) {
          continue;
        }
        tinymce.editors[instance].remove();
      }
    }
  }
};

Drupal.wysiwyg.editor.instance.tinymce = {
  addPlugin: function (plugin, pluginSettings) {
    if (typeof Drupal.wysiwyg.plugins[plugin] !== 'object') {
      return;
    }

    // Register plugin.
    tinymce.PluginManager.add('drupal_' + plugin, function (editor) {
      var button = {
        title: pluginSettings.title,
        image: pluginSettings.icon,
        onPostRender: function () {
          var self = this;
          editor.on('nodeChange', function (e) {
            // isNode: Return whether the plugin button should be enabled for
            // the current selection.
            if (typeof Drupal.wysiwyg.plugins[plugin].isNode == 'function') {
              self.active(Drupal.wysiwyg.plugins[plugin].isNode(e.element));
            }
          });
        }
      };
      if (typeof Drupal.wysiwyg.plugins[plugin].invoke == 'function') {
        button.onclick = function () {
          var data = {format: 'html', node: editor.selection.getNode(), content: editor.selection.getContent()};
          // TinyMCE creates a completely new instance for fullscreen mode.
          Drupal.wysiwyg.plugins[plugin].invoke(data, pluginSettings, editor.id);
        };
      }

      // Register the plugin button.
      editor.addButton('drupal_' + plugin, button);

      /**
       * Initialize the plugin, executed after the plugin has been created.
       *
       * @param ed
       *   The tinymce.Editor instance the plugin is initialized in.
       * @param url
       *   The absolute URL of the plugin location.
       */
      editor.on('init', function (e) {
        // Load custom CSS for editor contents on startup.
        if (pluginSettings.css) {
          editor.dom.loadCSS(pluginSettings.css);
        }

      });

      // Attach: Replace plain text with HTML representations.
      editor.on('beforeSetContent', function (e) {
        if (typeof Drupal.wysiwyg.plugins[plugin].attach === 'function') {
          e.content = Drupal.wysiwyg.plugins[plugin].attach(e.content, pluginSettings, e.target.id);
          e.content = Drupal.wysiwyg.editor.instance.tinymce.prepareContent(e.content);
        }
      });

      // Detach: Replace HTML representations with plain text.
      editor.on('getContent', function (e) {
        var editorId = (e.target.id === 'mce_fullscreen' ? e.target.getParam('fullscreen_editor_id') : e.target.id);
        if (typeof Drupal.wysiwyg.plugins[plugin].detach == 'function') {
          e.content = Drupal.wysiwyg.plugins[plugin].detach(e.content, pluginSettings, editorId);
        }
      });
    });
  },

  openDialog: function (dialog, params) {
    var instanceId = this.getInstanceId();
    var editor = tinymce.get(instanceId);
    editor.windowManager.open({
      file: dialog.url + '/' + instanceId,
      width: dialog.width,
      height: dialog.height,
      inline: 1
    }, params);
  },

  closeDialog: function (dialog) {
    var editor = tinymce.get(this.getInstanceId());
    editor.windowManager.close(dialog);
  },

  prepareContent: function (content) {
    // Certain content elements need to have additional DOM properties applied
    // to prevent this editor from highlighting an internal button in addition
    // to the button of a Drupal plugin.
    var specialProperties = {
      img: {class: 'mceItem'}
    };
    // No .outerHTML() in jQuery :(
    var $content = $('<div>' + content + '</div>');
    // Find all placeholder/replacement content of Drupal plugins.
    $content.find('.drupal-content').each(function () {
      // Recursively process DOM elements below this element to apply special
      // properties.
      var $drupalContent = $(this);
      $.each(specialProperties, function (element, properties) {
        $drupalContent.find(element).andSelf().each(function () {
          for (var property in properties) {
            if (property === 'class') {
              $(this).addClass(properties[property]);
            }
            else {
              $(this).attr(property, properties[property]);
            }
          }
        });
      });
    });
    return $content.html();
  },

  insert: function (content) {
    content = this.prepareContent(content);
    tinymce.get(this.field).insertContent(content);
  },

  setContent: function (content) {
    content = this.prepareContent(content);
    tinymce.get(this.field).setContent(content);
  },

  getContent: function () {
    return tinymce.get(this.getInstanceId()).getContent();
  },

  isFullscreen: function () {
    var editor = tinymce.get(this.field);
    return editor.plugins.fullscreen && editor.plugins.fullscreen.isFullscreen();
  },

  getInstanceId: function () {
    return this.field;
  }
};

})(jQuery);
