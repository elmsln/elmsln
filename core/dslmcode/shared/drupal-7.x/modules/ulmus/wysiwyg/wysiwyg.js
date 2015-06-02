(function($) {

// Keeps track of editor status during AJAX operations, active format and more.
// Always use getFieldInfo() to get a valid reference to the correct data.
var _fieldInfoStorage = Drupal.wysiwyg._fieldInfoStorage = (Drupal.wysiwyg._fieldInfoStorage || {});
// Keeps track of information relevant to each format, such as editor settings.
// Always use getFormatInfo() to get a reference to a format's data.
var _formatInfoStorage = _formatInfoStorage = (Drupal.wysiwyg._formatInfoStorage || {});

/**
 * Returns field specific editor data.
 *
 * @throws Error
 *   Exception thrown if data for an unknown field is requested.
 *   Summary fields are expected to use the same data as the main field.
 *
 * If a field id contains the delimiter '--', anything after that is dropped and
 * the remainder is assumed to be the id of an original field replaced by an
 * AJAX operation, due to how Drupal generates unique ids.
 * @see drupal_html_id()
 *
 * Do not modify the returned object unless you really know what you're doing.
 * No external code should need access to this, and it may likely change in the
 * future.
 *
 * Can be used to just test if data exists for a field by passing false/null as
 * the defaultData argument and check if the return value evaluates to true.
 *
 * @param fieldId
 *   The id of the field to get data for.
 * @param defaultData
 *   Used internally to set initial data for a field.
 *
 * @returns
 *   A reference to an object with the following properties:
 *   - activeFormat: A string with the active format id.
 *   - enabled: A boolean, true if the editor is attached.
 *   - formats: An object with one sub-object for each available format, holding
 *     format specific state data for this field.
 *   - summary: An optional string with the id of a corresponding summary field.
 *   - trigger: A string with the id of the format selector for the field.
 *   - getFormatInfo: Shortcut method to getFormatInfo(fieldInfo.activeFormat).
 */
function getFieldInfo(fieldId, defaultData) {
  if (!_fieldInfoStorage[fieldId]) {
    var baseFieldId = (fieldId.indexOf('--') === -1 ? fieldId : fieldId.substr(0, fieldId.indexOf('--')));
    if (!_fieldInfoStorage[baseFieldId]) {
      if (typeof defaultData !== 'undefined') {
        _fieldInfoStorage[baseFieldId] = defaultData;
      }
      else {
        throw new Error('Wysiwyg module has no information about field "' + fieldId + '"');
      }
    }
    return _fieldInfoStorage[baseFieldId];
  }
  return _fieldInfoStorage[fieldId];
}

/**
 * Returns format specific editor data.
 *
 * Do not modify the returned object unless you really know what you're doing.
 * No external code should need access to this, and it may likely change in the
 * future.
 *
 * Can be used to just test if data exists for a format by passing false/null as
 * the defaultData argument and check if the return value evaluates to true.
 *
 * @param formatId
 *   The id of a format to get data for.
 * @param defaultData
 *   Used internally to set initial data for a format.
 *
 * @returns
 *   A reference to an object with the following properties:
 *   - editor: A string with the id of the editor attached to the format.
 *     'none' if no editor profile is associated with the format.
 *   - enabled: True if the editor is active.
 *   - toggle: True if the editor can be toggled on/off by the user.
 *   - editorSettings: A structure holding editor settings for this format.
 */
function getFormatInfo(formatId, defaultData) {
  if (!_formatInfoStorage[formatId]) {
    if (typeof defaultData !== 'undefined') {
      _formatInfoStorage[formatId] = defaultData;
    }
    else {
      return {
        editor: 'none'
      };
    }
  }
  return _formatInfoStorage[formatId];
}

/**
 * Initialize editor libraries.
 *
 * Some editors need to be initialized before the DOM is fully loaded. The
 * init hook gives them a chance to do so.
 */
Drupal.wysiwygInit = function() {
  // This breaks in Konqueror. Prevent it from running.
  if (/KDE/.test(navigator.vendor)) {
    return;
  }
  jQuery.each(Drupal.wysiwyg.editor.init, function(editor) {
    // Clone, so original settings are not overwritten.
    this(jQuery.extend(true, {}, Drupal.settings.wysiwyg.configs[editor]));
  });
};

/**
 * Attach editors to input formats and target elements (f.e. textareas).
 *
 * This behavior searches for input format selectors and formatting guidelines
 * that have been preprocessed by Wysiwyg API. All CSS classes of those elements
 * with the prefix 'wysiwyg-' are parsed into input format parameters, defining
 * the input format, configured editor, target element id, and variable other
 * properties, which are passed to the attach/detach hooks of the corresponding
 * editor.
 *
 * Furthermore, an "enable/disable rich-text" toggle link is added after the
 * target element to allow users to alter its contents in plain text.
 *
 * This is executed once, while editor attach/detach hooks can be invoked
 * multiple times.
 *
 * @param context
 *   A DOM element, supplied by Drupal.attachBehaviors().
 */
Drupal.behaviors.attachWysiwyg = {
  attach: function (context, settings) {
    // This breaks in Konqueror. Prevent it from running.
    if (/KDE/.test(navigator.vendor)) {
      return;
    }

    $('.wysiwyg:input', context).once('wysiwyg', function () {
      // Skip processing if the trigger is unknown or does not exist in this
      // document. Can happen after a form was removed but Drupal.ajax keeps a
      // lingering reference to the form and calls Drupal.attachBehaviors().
      var $this = $('#' + this.id, document), trigger = settings.wysiwyg.triggers[this.id];
      if (!trigger || !$this.length) {
        return;
      }

      var $selectbox;
      if (trigger.select) {
        // Specifically target input elements in case selectbox wrappers have
        // hidden the real element and cloned its attributes.
        $selectbox = $('#' + trigger.select + ':input', context);
      }

      // Create the field info if this field (or one with the same base id)
      // does not already exist.
      var fieldInfo = getFieldInfo(trigger.field, {
        activeFormat: 'format' + ($selectbox ? $selectbox.val() : trigger.activeFormat),
        formats: {},
        resizable: trigger.resizable,
        getFormatInfo: function () {
          return getFormatInfo(this.activeFormat);
        }
      });
      // Always update these since Drupal generates new ids on AJAX calls.
      if (trigger.select) {
        fieldInfo.select = trigger.select;
      }
      fieldInfo.summary = trigger.summary;
      for (var format in trigger) {
        if (format.indexOf('format') != 0) {
          continue;
        }
        if (!fieldInfo.formats[format]) {
          fieldInfo.formats[format] = {
            'enabled': trigger[format].status
          }
          if (trigger[format].skip_summary) {
            fieldInfo.formats[format].skip_summary = true;
          }
        }
        // Build the cache of format/profile settings.
        var formatInfo = getFormatInfo(format, null);
        if (!formatInfo) {
          var formatSettings = {};
          // Settings can be missing if the editor isn't configured yet.
          if (settings.wysiwyg.configs[trigger[format].editor]) {
            formatSettings = settings.wysiwyg.configs[trigger[format].editor][format];
          }
          formatInfo = getFormatInfo(format, {
            editor: trigger[format].editor,
            toggle: trigger[format].toggle,
            editorSettings: processObjectTypes(formatSettings)
          });
        }
      }
      fieldInfo.enabled = fieldInfo.formats[fieldInfo.activeFormat] && fieldInfo.formats[fieldInfo.activeFormat].enabled;
      // Directly attach this editor, if the input format is enabled or there is
      // only one input format at all.
      Drupal.wysiwygAttach(context, trigger.field);
      // Attach onChange handlers to input format selector elements.
      if ($selectbox && $selectbox.is('select')) {
        $selectbox.change((function(context, fieldId) {
          return function (event) {
            // Field state is fetched by reference.
            var currentField = getFieldInfo(fieldId);
            // Save the state of the current format.
            if (currentField.formats[currentField.activeFormat]) {
              currentField.formats[currentField.activeFormat].enabled = currentField.enabled;
            }
            // Switch format/profile.
            currentField.activeFormat = 'format' + this.value;
            // Load the state from the new format.
            if (currentField.formats[currentField.activeFormat]) {
              currentField.enabled = currentField.formats[currentField.activeFormat].enabled;
            }
            else {
              currentField.enabled = false;
            }
            // Attaching again will use the changed field state.
            Drupal.wysiwygAttach(context, fieldId);
          }
        })(context, trigger.field));
      }
      // Detach any editor when the containing form is submitted.
      $this.closest('form').submit((function (context, fieldId) {
        return function (event) {
          // Do not detach if the event was cancelled.
          if (event.isDefaultPrevented()) {
            return;
          }
          Drupal.wysiwygDetach(context, fieldId, 'serialize');
        }
      })(context, trigger.field));
    });
  },

  detach: function (context, settings, trigger) {
    var wysiwygs;
    // The 'serialize' trigger indicates that we should simply update the
    // underlying element with the new text, without destroying the editor.
    if (trigger == 'serialize') {
      // Removing the wysiwyg-processed class guarantees that the editor will
      // be reattached. Only do this if we're planning to destroy the editor.
      wysiwygs = $('.wysiwyg-processed:input', context);
    }
    else {
      wysiwygs = $('.wysiwyg:input', context).removeOnce('wysiwyg');
    }
    wysiwygs.each(function () {
      Drupal.wysiwygDetach(context, this.id, trigger);
    });
  }
};

/**
 * Attach an editor to a target element.
 *
 * Detaches any existing instance for the field before attaching a new instance
 * based on the current state of the field. Editor settings and state
 * information is fetched  based on the element id and get cloned first, so they
 * cannot be overridden. After attaching the editor, the toggle link is shown
 * again, except in case we are attaching no editor.
 *
 * Also attaches editors to the summary field, if available.
 *
 * @param context
 *   A DOM element, supplied by Drupal.attachBehaviors().
 * @param fieldId
 *   The id of an element to attach an editor to.
 */
Drupal.wysiwygAttach = function(context, fieldId) {
  var fieldInfo = getFieldInfo(fieldId),
      formatInfo = fieldInfo.getFormatInfo(),
      editor = formatInfo.editor,
      previousStatus = status,
      previousEditor = 'none',
      doSummary = (fieldInfo.summary && (!fieldInfo.formats[fieldInfo.activeFormat] || !fieldInfo.formats[fieldInfo.activeFormat].skip_summary));
  if (Drupal.wysiwyg.instances[fieldId]) {
    previousStatus = Drupal.wysiwyg.instances[fieldId]['status'];
    previousEditor = Drupal.wysiwyg.instances[fieldId].editor;
  }
  // Detach any previous editor instance if enabled, else remove the grippie.
  detachFromField(context, {'editor': previousEditor, 'status': previousStatus, 'field': fieldId, 'resizable': fieldInfo.resizable}, 'unload');
  if (doSummary) {
    detachFromField(context, {'editor': previousEditor, 'status': previousStatus, 'field': fieldInfo.summary, 'resizable': fieldInfo.resizable}, 'unload');
  }
  // Store this field id, so (external) plugins can use it.
  // @todo Wrong point in time. Probably can only supported by editors which
  //   support an onFocus() or similar event.
  Drupal.wysiwyg.activeId = fieldId;
  // Attach or update toggle link, if enabled.
  Drupal.wysiwygAttachToggleLink(context, fieldId);
  // Clone editor settings to be sure they don't get altered.
  var editorSettings = jQuery.extend(true, {}, formatInfo.editorSettings);
  // Attach to main field.
  attachToField(context, {'status': fieldInfo.enabled, 'editor': editor, 'field': fieldId, 'format': fieldInfo.activeFormat, 'resizable': fieldInfo.resizable}, editorSettings);
  // Attach to summary field.
  if (doSummary) {
    // If the summary wrapper is hidden, attach when it's made visible.
    if ($('#' + fieldInfo.summary).parents('.text-summary-wrapper').is(':visible')) {
      attachToField(context, {'status': fieldInfo.enabled, 'editor': editor, 'field': fieldInfo.summary, 'format': fieldInfo.activeFormat, 'resizable': fieldInfo.resizable}, editorSettings);
    }
    else {
      // Unbind any existing click handler to avoid double toggling.
      $('#' + fieldId).parents('.text-format-wrapper').find('.link-edit-summary').unbind('click.wysiwyg').bind('click.wysiwyg', function () {
        attachToField(context, {'status': fieldInfo.enabled, 'editor': editor, 'field': fieldInfo.summary, 'format': fieldInfo.activeFormat, 'resizable': fieldInfo.resizable}, editorSettings);
        $(this).unbind('click.wysiwyg');
      });
    }
  }
};

/**
 * Helper to prepare and attach an editor for a single field.
 *
 * Creates the 'instance' object under Drupal.wysiwyg.instances[fieldId].
 *
 * @param context
 *   A DOM element, supplied by Drupal.attachBehaviors().
 * @param params
 *   An object containing state information for the editor with the following
 *   properties:
 *   - 'status': A boolean stating whether the editor is currently active. If
 *     false, the default textarea behaviors will be attached instead (aka the
 *     'none' editor implementation).
 *   - 'editor': The internal name of the editor to attach when active.
 *   - 'field': The field id to use as a output target for the editor.
 *   - 'format': The name of the active text format (prefixed 'format').
 *   - 'resizable': A boolean indicating whether the original textarea was
 *      resizable.
 *   Note: This parameter is passed directly to the editor implementation and
 *   needs to have been reconstructed or cloned before attaching.
 * @param editorSettings
 *   An object containing all the settings the editor needs for this field.
 *   Settings are automatically cloned to prevent editors from modifying them.
 */
function attachToField(context, params, editorSettings) {
  // If the editor isn't active, attach default behaviors instead.
  var editor = (params.status ? params.editor : 'none');
  // (Re-)initialize field instance.
  Drupal.wysiwyg.instances[params.field] = {};
  // Provide all input format parameters to editor instance.
  jQuery.extend(true, Drupal.wysiwyg.instances[params.field], params);
  // Provide editor callbacks for plugins, if available.
  if (typeof Drupal.wysiwyg.editor.instance[editor] == 'object') {
    jQuery.extend(true, Drupal.wysiwyg.instances[params.field], Drupal.wysiwyg.editor.instance[editor]);
  }
  // Settings are deep merged (cloned) to prevent editor implementations from
  // permanently modifying them while attaching.
  if (typeof Drupal.wysiwyg.editor.attach[editor] == 'function') {
    Drupal.wysiwyg.editor.attach[editor](context, params, params.status ? jQuery.extend(true, {}, editorSettings) : {});
  }
}

/**
 * Detach all editors from a target element.
 *
 * Ensures Drupal's original textfield resize functionality is restored if
 * enabled and the triggering reason is 'unload'.
 *
 * Also detaches editors from the summary field, if available.
 *
 * @param context
 *   A DOM element, supplied by Drupal.detachBehaviors().
 * @param fieldId
 *   The id of an element to attach an editor to.
 * @param trigger
 *   A string describing what is causing the editor to be detached.
 *   - 'serialize': The editor normally just syncs its contents to the original
 *     textarea for value serialization before an AJAX request.
 *   - 'unload': The editor is to be removed completely and the original
 *     textarea restored.
 *
 * @see Drupal.detachBehaviors()
 */
Drupal.wysiwygDetach = function (context, fieldId, trigger) {
  var fieldInfo = getFieldInfo(fieldId),
      editor = fieldInfo.getFormatInfo().editor,
      trigger = trigger || 'unload',
      previousStatus = (Drupal.wysiwyg.instances[fieldId] && Drupal.wysiwyg.instances[fieldId]['status']);
  // Detach from main field.
  detachFromField(context, {'editor': editor, 'status': previousStatus, 'field': fieldId, 'resizable': fieldInfo.resizable}, trigger);
  if (trigger == 'unload') {
    // Attach the resize behavior by forcing status to false. Other values are
    // intentionally kept the same to show which editor is normally attached.
    attachToField(context, {'editor': editor, 'status': false, 'format': fieldInfo.activeFormat, 'field': fieldId, 'resizable': fieldInfo.resizable});
    Drupal.wysiwygAttachToggleLink(context, fieldId);
  }
  // Detach from summary field.
  if (fieldInfo.summary && Drupal.wysiwyg.instances[fieldInfo.summary]) {
    // The "Edit summary" click handler could re-enable the editor by mistake.
    $('#' + fieldId).parents('.text-format-wrapper').find('.link-edit-summary').unbind('click.wysiwyg');
    detachFromField(context, {'editor': editor, 'status': previousStatus, 'field': fieldInfo.summary, 'resizable': fieldInfo.resizable}, trigger);
    if (trigger == 'unload') {
      attachToField(context, {'editor': editor, 'status': false, 'format': fieldInfo.activeFormat, 'field': fieldInfo.summary, 'resizable': fieldInfo.resizable});
    }
  }
};

/**
 * Helper to detach and clean up after an editor for a single field.
 *
 * Removes the 'instance' object under Drupal.wysiwyg.instances[fieldId].
 *
 * @param context
 *   A DOM element, supplied by Drupal.detachBehaviors().
 * @param params
 *   An object containing state information for the editor with the following
 *   properties:
 *   - 'status': A boolean stating whether the editor is currently active. If
 *     false, the default textarea behaviors will be attached instead (aka the
 *     'none' editor implementation).
 *   - 'editor': The internal name of the editor to attach when active.
 *   - 'field': The field id to use as a output target for the editor.
 *   - 'format': The name of the active text format (prefixed 'format').
 *   - 'resizable': A boolean indicating whether the original textarea was
 *      resizable.
 *   Note: This parameter is passed directly to the editor implementation and
 *   needs to have been reconstructed or cloned before detaching.
 * @param trigger
 *   A string describing what is causing the editor to be detached.
 *   - 'serialize': The editor normally just syncs its contents to the original
 *     textarea for value serialization before an AJAX request.
 *   - 'unload': The editor is to be removed completely and the original
 *     textarea restored.
 *
 * @see Drupal.wysiwygDetach()
 **/
function detachFromField(context, params, trigger) {
  var editor = (params.status ? params.editor : 'none');
  if (jQuery.isFunction(Drupal.wysiwyg.editor.detach[editor])) {
    Drupal.wysiwyg.editor.detach[editor](context, params, trigger);
  }
  if (trigger == 'unload') {
    delete Drupal.wysiwyg.instances[params.field];
  }
}

/**
 * Append or update an editor toggle link to a target element.
 *
 * @param context
 *   A DOM element, supplied by Drupal.attachBehaviors().
 * @param fieldId
 *   The id of an element to attach an editor to.
 */
Drupal.wysiwygAttachToggleLink = function(context, fieldId) {
  var fieldInfo = getFieldInfo(fieldId),
      editor = fieldInfo.getFormatInfo().editor;
  if (!fieldInfo.getFormatInfo().toggle) {
    // Otherwise, ensure that toggle link is hidden.
    $('#wysiwyg-toggle-' + fieldId).hide();
    return;
  }
  if (!$('#wysiwyg-toggle-' + fieldId, context).length) {
    var text = document.createTextNode(fieldInfo.enabled ? Drupal.settings.wysiwyg.disable : Drupal.settings.wysiwyg.enable),
      a = document.createElement('a'),
      div = document.createElement('div');
    $(a).attr({ id: 'wysiwyg-toggle-' + fieldId, href: 'javascript:void(0);' }).append(text);
    $(div).addClass('wysiwyg-toggle-wrapper').append(a);
    if ($('#' + fieldInfo.select).closest('.fieldset-wrapper').prepend(div).length == 0) {
      // Fall back to inserting the link right after the field.
      $('#' + fieldId).after(div);
    };
  }
  $('#wysiwyg-toggle-' + fieldId, context)
    .html(fieldInfo.enabled ? Drupal.settings.wysiwyg.disable : Drupal.settings.wysiwyg.enable).show()
    .unbind('click.wysiwyg')
    .bind('click.wysiwyg', { 'fieldId': fieldId, 'context': context }, Drupal.wysiwyg.toggleWysiwyg);

  // Hide toggle link in case no editor is attached.
  if (editor == 'none') {
    $('#wysiwyg-toggle-' + fieldId).hide();
  }
};

/**
 * Callback for the Enable/Disable rich editor link.
 */
Drupal.wysiwyg.toggleWysiwyg = function (event) {
  var context = event.data.context,
      fieldId = event.data.fieldId,
      fieldInfo = getFieldInfo(fieldId);
  // Toggling the enabled state indirectly toggles use of the 'none' editor.
  if (fieldInfo.enabled) {
    fieldInfo.enabled = false;
    Drupal.wysiwygDetach(context, fieldId, 'unload');
  }
  else {
    fieldInfo.enabled = true;
    Drupal.wysiwygAttach(context, fieldId);
  }
  fieldInfo.formats[fieldInfo.activeFormat].enabled = fieldInfo.enabled;
}

/**
 * Convert JSON type placeholders into the actual types.
 *
 * Recognizes function references (callbacks) and Regular Expressions.
 *
 * To create a callback, pass in an object with the following properties:
 * - 'drupalWysiwygType': Must be set to 'callback'.
 * - 'name': A string with the name of the callback, use
 *   'object.subobject.method' syntax for methods in nested objects.
 * - 'context': An optional string with the name of an object for overriding
 *   'this' inside the function. Use 'object.subobject' syntax for nested
 *   objects. Defaults to the window object.
 *
 * To create a RegExp, pass in an object with the following properties:
 * - 'drupalWysiwygType: Must be set to 'regexp'.
 * - 'regexp': The Regular Expression as a string, without / wrappers.
 * - 'modifiers': An optional string with modifiers to set on the RegExp object.
 *
 * @param json
 *  The json argument with all recognized type placeholders replaced by the real
 *  types.
 *
 * @return The JSON object with placeholder types replaced.
 */
function processObjectTypes(json) {
  var out = null;
  if (typeof json != 'object') {
    return json;
  }
  out = new json.constructor();
  if (json.drupalWysiwygType) {
    switch (json.drupalWysiwygType) {
      case 'callback':
        out = callbackWrapper(json.name, json.context);
        break;
      case 'regexp':
        out = new RegExp(json.regexp, json.modifiers ? json.modifiers : undefined);
        break;
      default:
        out.drupalWysiwygType = json.drupalWysiwygType;
    }
  }
  else {
    for (var i in json) {
      if (json.hasOwnProperty(i) && json[i] && typeof json[i] == 'object') {
        out[i] = processObjectTypes(json[i]);
      }
      else {
        out[i] = json[i];
      }
    }
  }
  return out;
}

/**
 * Convert function names into function references.
 *
 * @param name
 *  The name of a function to use as callback. Use the 'object.subobject.method'
 *  syntax for methods in nested objects.
 * @param context
 *  An optional string with the name of an object for overriding 'this' inside
 *  the function. Use 'object.subobject' syntax for nested objects. Defaults to
 *  the window object.
 *
 * @return
 *  A function which will call the named function or method in the proper
 *  context, passing through arguments and return values.
 */
function callbackWrapper(name, context) {
  var namespaces = name.split('.'), func = namespaces.pop(), obj = window;
  for (var i = 0; obj && i < namespaces.length; i++) {
    obj = obj[namespaces[i]];
  }
  if (!obj) {
    throw "Wysiwyg: Unable to locate callback " + namespaces.join('.') + "." + func + "()";
  }
  if (!context) {
    context = obj;
  }
  else if (typeof context == 'string'){
    namespaces = context.split('.');
    context = window;
    for (i = 0; context && i < namespaces.length; i++) {
      context = context[namespaces[i]];
    }
    if (!context) {
      throw "Wysiwyg: Unable to locate context object " + namespaces.join('.');
    }
  }
  if (typeof obj[func] != 'function') {
    throw "Wysiwyg: " + func + " is not a callback function";
  }
  return function () {
    return obj[func].apply(context, arguments);
  }
}

/**
 * Allow certain editor libraries to initialize before the DOM is loaded.
 */
Drupal.wysiwygInit();

// Respond to CTools detach behaviors event.
$(document).unbind('CToolsDetachBehaviors.wysiwyg').bind('CToolsDetachBehaviors.wysiwyg', function(event, context) {
  Drupal.behaviors.attachWysiwyg.detach(context, {}, 'unload');
});

})(jQuery);
