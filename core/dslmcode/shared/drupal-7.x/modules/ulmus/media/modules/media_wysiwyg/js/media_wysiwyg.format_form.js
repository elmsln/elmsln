
/**
 *  @file
 *  Attach behaviors to formatter radio select when selecting a media's display
 *  formatter.
 */

(function ($) {
namespace('Drupal.media.formatForm');

Drupal.media.mediaFormatSelected = {};

Drupal.behaviors.mediaFormatForm = {
  attach: function (context, settings) {
    // Add the "Submit" button inside the IFRAME that trigger the behavior of
    // the hidden "OK" button that is outside the IFRAME.
    // @see Drupal.media.browser.validateButtons() for more details.

    // @note I think this should be handled in media.browser.js in
    // Drupal.media.browser.validateButtons but I'm not sure how crufty this
    // particular functionality is. We should evaluate if it is still needed.

    // @TODO can these be added to the content being displayed via form_alter?

    // Adding the buttons should only be done once in order to prevent multiple
    // buttons from being added if part of the form is updated via AJAX
    $('#media-wysiwyg-format-form').once('format', function() {
      $('<a class="button fake-ok">' + Drupal.t('Submit') + '</a>').appendTo($('#media-wysiwyg-format-form')).bind('click', Drupal.media.formatForm.submit);
    });
  }
};

Drupal.media.formatForm.getEditorContent = function(fieldKey) {
  // This is the default implementation of an overridable function: 
  // Each javascript rich-text editor module should provide an override implementation 
  // of this function which fetches content from the appropriate editor-specific variable.
  
  // This current implementation explicitly handles the editors from the
  // WYSIWYG and Media CKEditor modules: it should be modified to remove that
  // as soon as each module has been confirmed to provide their own implementation.

  if (Drupal.wysiwyg && Drupal.wysiwyg.instances[fieldKey] && Drupal.wysiwyg.instances[fieldKey].status) {
    // Retrieve the content from the editor provided by the WYSIWYG Module.
    // Remove this case once the WYSIWYG module provides an override for this function.
    return Drupal.wysiwyg.instances[fieldKey].getContent();
  }
  else if (typeof CKEDITOR !== 'undefined' && CKEDITOR.instances[fieldKey]) {
    // Retrieve the content from the editor provided by the Media CKEditor Module.
    // Remove this case once the Media CKEditor module provides an override for this function.
    return CKEDITOR.instances[fieldKey].getData();
  }
  else {
    // Default case => no known WYSIWYG editor.
    return null;
  }
}

Drupal.media.formatForm.escapeFieldInput = function(input) {
  // This is the default implementation of an overridable function: It is
  // intended to allow for the escaping of the user input from the format form.
  // No escaping is done here, but this allows other modules to escape the input
  // by overriding this function.
  return input;
}

Drupal.media.formatForm.getOptions = function () {
  // Get all the values
  var ret = {};
  // Keep track of multi-value fields.
  var fieldDelta = {};

  $.each($('#media-wysiwyg-format-form .fieldset-wrapper *').serializeArray(), function (i, field) {

    // Support multi-value fields, which show up here with [] at the end.
    if ('[]' == field.name.slice(-2)) {
      if (typeof fieldDelta[field.name] === 'undefined') {
        fieldDelta[field.name] = 0;
      }
      else {
        fieldDelta[field.name] += 1;
      }
      field.name = field.name.replace('[]', '[' + fieldDelta[field.name] + ']');
    }

    ret[field.name] = Drupal.media.formatForm.escapeFieldInput(field.value);

    // When a field uses a WYSIWYG format, the value needs to be extracted and encoded.
    if (field.name.match(/\[format\]/i)) {
      field.name = field.name.replace(/\[format\]/i, '[value]');
      field.key = 'edit-' + field.name.replace(/[_\[]/g, '-').replace(/[\]]/g, '');

      // Attempt to retrieve content for this field from any associated javascript rich-text editor.
      var editorContent = Drupal.media.formatForm.getEditorContent(field.key);
      // Find content or an empty string (in case existing content was removed).
      if (editorContent || editorContent === '') {
        // Replace the already-cached value with the value from the editor.
        ret[field.name] = editorContent;
      }
      else {
        // An editor was not used for this field - either because none was configured for the selected format,
        // or possibly because the user chose to revert to the plain-text editor (CKEditor allows that).
        // Replace the already-cached value with the raw value from the long-text field value.
        // (Replacment is needed because this function may be invoked multiple times on the same field,
        // and so the cached value may already have been encoded - we don't want to double-encode it!)
        ret[field.name] = $('#' + field.key).val();
      }

      // Encode the formatted value to play nicely within JSON.
      // (It could contain HTML and other quoted entities, no matter what sort of editor was used)
      ret[field.name] = encodeURIComponent(ret[field.name]);
    }
  });

  return ret;
};

Drupal.media.formatForm.getFormattedMedia = function () {
  var formatType = $("#edit-format").val();
  return { type: formatType, options: Drupal.media.formatForm.getOptions(), html: Drupal.settings.media.formatFormFormats[formatType] };
};

Drupal.media.formatForm.submit = function () {
  // @see Drupal.behaviors.mediaFormatForm.attach().
  var buttons = $(parent.window.document.body).find('#mediaStyleSelector').parent('.ui-dialog').find('.ui-dialog-buttonpane button');
  buttons[0].click();
}

})(jQuery);
