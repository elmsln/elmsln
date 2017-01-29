var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Adds a file upload field to the form.
 *
 * @param {mixed} parent
 * @param {object} field
 * @param {mixed} params
 * @param {function} setValue
 * @returns {ns.File}
 */
ns.File = function (parent, field, params, setValue) {
  var self = this;

  // Initialize inheritance
  ns.FileUploader.call(self, field);

  this.parent = parent;
  this.field = field;
  this.params = params;
  this.setValue = setValue;
  this.library = parent.library + '/' + field.name;

  if (params !== undefined) {
    this.copyright = params.copyright;
  }

  this.changes = [];
  this.passReadies = true;
  parent.ready(function () {
    self.passReadies = false;
  });

  // Create remove file dialog
  this.confirmRemovalDialog = new H5P.ConfirmationDialog({
    headerText: H5PEditor.t('core', 'removeFile'),
    dialogText: H5PEditor.t('core', 'confirmRemoval', {':type': 'file'})
  }).appendTo(document.body);

  // Remove file on confirmation
  this.confirmRemovalDialog.on('confirmed', function () {
    delete self.params;
    self.setValue(self.field);
    self.addFile();

    for (var i = 0; i < self.changes.length; i++) {
      self.changes[i]();
    }
  });

  // When uploading starts
  self.on('upload', function () {
    // Insert throbber
    self.$file.html('<div class="h5peditor-uploading h5p-throbber">' + ns.t('core', 'uploading') + '</div>');

    // Clear old error messages
    self.$errors.html('');
  });

  // Handle upload complete
  self.on('uploadComplete', function (event) {
    var result = event.data;

    try {
      if (result.error) {
        throw result.error;
      }

      self.params = self.params || {};
      self.params.path = result.data.path;
      self.params.mime = result.data.mime;
      self.params.copyright = self.copyright;

      // Make it possible for other widgets to process the result
      self.trigger('fileUploaded', result.data);

      self.setValue(self.field, self.params);

      for (var i = 0; i < self.changes.length; i++) {
        self.changes[i](self.params);
      }
    }
    catch (error) {
      self.$errors.append(ns.createError(error));
    }

    self.addFile();
  });
};

ns.File.prototype = Object.create(ns.FileUploader.prototype);
ns.File.prototype.constructor = ns.File;

/**
 * Append field to the given wrapper.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
ns.File.prototype.appendTo = function ($wrapper) {
  var self = this;

  var fileHtml =
    '<div class="file"></div>' +
    '<a class="h5p-copyright-button" href="#">' + ns.t('core', 'editCopyright') + '</a>' +
    '<div class="h5p-editor-dialog">' +
      '<a href="#" class="h5p-close" title="' + ns.t('core', 'close') + '"></a>' +
    '</div>';

  var html = ns.createFieldMarkup(this.field, fileHtml);

  var $container = ns.$(html).appendTo($wrapper);
  this.$copyrightButton = $container.find('.h5p-copyright-button');
  this.$file = $container.find('.file');
  this.$errors = $container.find('.h5p-errors');
  this.addFile();

  var $dialog = $container.find('.h5p-editor-dialog');
  $container.find('.h5p-copyright-button').add($dialog.find('.h5p-close')).click(function () {
    $dialog.toggleClass('h5p-open');
    return false;
  });

  var group = new ns.widgets.group(self, ns.copyrightSemantics, self.copyright, function (field, value) {
    if (self.params !== undefined) {
      self.params.copyright = value;
    }
    self.copyright = value;
  });
  group.appendTo($dialog);
  group.expand();
  group.$group.find('.title').remove();
  this.children = [group];
};


/**
 * Sync copyright between all video files.
 *
 * @returns {undefined}
 */
ns.File.prototype.setCopyright = function (value) {
  this.copyright = this.params.copyright = value;
};


/**
 * Creates thumbnail HTML and actions.
 *
 * @returns {Boolean}
 */
ns.File.prototype.addFile = function () {
  var that = this;

  if (this.params === undefined) {
    this.$file.html(
      '<a href="#" class="add" title="' + ns.t('core', 'addFile') + '">' +
        '<div class="h5peditor-field-file-upload-text">' + ns.t('core', 'add') + '</div>' +
      '</a>'
    ).children('.add').click(function () {
      that.openFileSelector();
      return false;
    });
    this.$copyrightButton.addClass('hidden');
    return;
  }

  var thumbnail;
  if (this.field.type === 'image') {
    thumbnail = {};
    thumbnail.path = H5P.getPath(this.params.path, H5PEditor.contentId);
    thumbnail.height = 100;
    if (this.params.width !== undefined) {
      thumbnail.width = thumbnail.height * (this.params.width / this.params.height);
    }
  }
  else {
    thumbnail = ns.fileIcon;
  }

  this.$file.html('<a href="#" title="' + ns.t('core', 'changeFile') + '" class="thumbnail"><img ' + (thumbnail.width === undefined ? '' : ' width="' + thumbnail.width + '"') + 'height="' + thumbnail.height + '" alt="' + (this.field.label === undefined ? '' : this.field.label) + '"/><a href="#" class="remove" title="' + ns.t('core', 'removeFile') + '"></a></a>').children(':eq(0)').click(function () {
    that.openFileSelector();
    return false;
  }).children('img').attr('src', thumbnail.path).end().next().click(function (e) {
    that.confirmRemovalDialog.show(H5P.jQuery(this).offset().top);
    return false;
  });
  that.$copyrightButton.removeClass('hidden');
};

/**
 * Validate this item
 */
ns.File.prototype.validate = function () {
  return true;
};

/**
 * Remove this item.
 */
ns.File.prototype.remove = function () {
  // TODO: Check what happens when removed during upload.
  this.$file.parent().remove();
};

/**
 * Collect functions to execute once the tree is complete.
 *
 * @param {function} ready
 * @returns {undefined}
 */
ns.File.prototype.ready = function (ready) {
  if (this.passReadies) {
    this.parent.ready(ready);
  }
  else {
    ready();
  }
};

// Tell the editor what widget we are.
ns.widgets.file = ns.File;
