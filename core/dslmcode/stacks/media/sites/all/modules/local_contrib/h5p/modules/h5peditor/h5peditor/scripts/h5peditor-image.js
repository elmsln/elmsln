/*global H5P*/
var H5PEditor = H5PEditor || {};
var ns = H5PEditor;

/**
 * Adds an image upload field with image editing tool to the form.
 *
 * @param {Object} parent Parent widget of this widget
 * @param {Object} field Semantic fields
 * @param {Object} params Existing image parameters
 * @param {function} setValue Function for updating parameters
 * @returns {ns.widgets.image}
 */
ns.widgets.image = function (parent, field, params, setValue) {
  ns.File.call(this, parent, field, params, setValue);
  var self = this;

  this.parent = parent;
  this.field = field;
  this.params = params;
  this.setValue = setValue;
  this.library = parent.library + '/' + field.name;

  if (params !== undefined) {
    this.copyright = params.copyright;
  }

  // Keep track of editing image
  this.isEditing = false;

  // Keep track of type of image that is being uploaded
  this.isOriginalImage = false;

  this.changes = [];
  this.passReadies = true;
  parent.ready(function () {
    self.passReadies = false;
  });
};

ns.widgets.image.prototype = Object.create(ns.File.prototype);
ns.widgets.image.prototype.constructor = ns.widgets.image;

/**
 * Append field to the given wrapper.
 *
 * @param {jQuery} $wrapper
 */
ns.widgets.image.prototype.appendTo = function ($wrapper) {
  var self = this;
  ns.File.addIframe();

  var label = '';
  if (this.field.label !== 0) {
    var labelString = this.field.label === undefined ? this.field.name : this.field.label;
    label = '<span class="h5peditor-label">' + labelString + '</span>';
  }

  var htmlString = label + '<div class="file"></div>' +
    '<div class="h5p-editor-image-buttons">' +
      '<button class="h5p-editing-image-button">' + ns.t('core', 'editImage') + '</button>' +
      '<button class="h5p-copyright-button">' + ns.t('core', 'editCopyright') + '</button>' +
    '</div>' +
    '<div class="h5p-editor-dialog">' +
      '<a href="#" class="h5p-close" title="' + ns.t('core', 'close') + '"></a>' +
    '</div>';

  var html = ns.createItem(this.field.type, htmlString, this.field.description);
  var $container = ns.$(html).appendTo($wrapper);
  this.$editImage = $container.find('.h5p-editing-image-button');
  this.$file = $container.find('.file');
  this.$errors = $container.find('.h5p-errors');
  this.addFile();

  var $dialog = $container.find('.h5p-editor-dialog');
  $container.find('.h5p-copyright-button').add($dialog.find('.h5p-close')).click(function () {
    $dialog.toggleClass('h5p-open');
    return false;
  });

  var editImagePopup = new H5PEditor.ImageEditingPopup(this.field.ratio);
  editImagePopup.on('savedImage', function (e) {

    // Not editing any longer
    self.isEditing = false;

    // No longer a original image
    self.isOriginalImage = false;

    // Set current source as original image, if no original image
    if (!self.params.originalImage) {
      self.params.originalImage = {
        path: self.params.path,
        mime: self.params.mime,
        height: self.params.height,
        width: self.params.width
      };
    }

    // Set new source as current image
    self.setUploadingThrobber();
    self.setImageChangeCallback();
    ns.File.$data.val(e.data);
    ns.File.$field.val(JSON.stringify(self.field));
    ns.File.$file.change();
  });

  editImagePopup.on('resetImage', function () {
    var imagePath = self.params.originalImage ? self.params.originalImage.path
      : self.params.path;
    var imageSrc = H5P.getPath(imagePath, H5PEditor.contentId);
    editImagePopup.setImage(imageSrc);
  });

  editImagePopup.on('canceled', function () {
    self.isEditing = false;
  });

  editImagePopup.on('initialized', function () {
    // Remove throbber from image
    self.$editImage.removeClass('loading');
  });

  $container.find('.h5p-editing-image-button').click(function () {
    if (self.params && self.params.path) {
      var imageSrc;
      if (!self.isEditing) {
        imageSrc = H5P.getPath(self.params.path, H5PEditor.contentId);
        self.isEditing = true;
      }
      self.$editImage.toggleClass('loading');

      // Add throbber to image
      editImagePopup.show(ns.$(this).offset(), imageSrc);
    }
  });

  var group = new ns.widgets.group(self, ns.copyrightSemantics, self.copyright,
    function (field, value) {
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
 * Sync copyright.
 */
ns.widgets.image.prototype.setCopyright = function (value) {
  this.copyright = this.params.copyright = value;
};


/**
 * Creates thumbnail HTML and actions.
 *
 * @returns {boolean} True if file was added, false if file was removed
 */
ns.widgets.image.prototype.addFile = function () {
  var that = this;

  if (this.params === undefined) {

    // No image look
    this.$file
      .html('<a href="#" class="add" title="' + ns.t('core', 'addFile') + '"></a>')
      .children('.add')
      .click(function () {
        that.uploadFile();
        return false;
      });

    // Remove edit image button
    this.$editImage.addClass('hidden');
    this.isEditing = false;

    return false;
  }

  var source = H5P.getPath(this.params.path, H5PEditor.contentId);
  var thumbnail = {};
  thumbnail.path = source;
  thumbnail.height = 100;
  if (this.params.width !== undefined) {
    thumbnail.width = thumbnail.height * (this.params.width / this.params.height);
  }

  var thumbnailWidth = thumbnail.width === undefined ? '' : ' width="' + thumbnail.width + '"';
  var altText = (this.field.label === undefined ? '' : this.field.label);
  var fileHtmlString =
    '<a href="#" title="' + ns.t('core', 'changeFile') + '" class="thumbnail">' +
      '<img ' + thumbnailWidth + 'height="' + thumbnail.height + '" alt="' + altText + '"/>' +
    '</a>' +
    '<a href="#" class="remove" title="' + ns.t('core', 'removeFile') + '"></a>';

  this.$file.html(fileHtmlString)
    .children(':eq(0)')
    .click(function () {
      that.uploadFile();
      return false;
    })
    .children('img')
    .attr('src', thumbnail.path)
    .end()
    .next()
    .click(function () {
      if (!window.confirm(ns.t('core', 'confirmRemoval', {':type': 'file'}))) {
        return false;
      }
      that.removeImage();
      return false;
    });

  // Uploading original image
  that.$editImage.removeClass('hidden');

  // Notify listeners that image was changed to params
  that.trigger('changedImage', this.params);

  return true;
};

/**
 * Set callback for when an image has been uploaded.
 */
ns.widgets.image.prototype.setImageChangeCallback = function () {
  var that = this;

  ns.File.callback = function (err, result) {
    try {
      if (err) {
        throw err;
      }

      that.params = that.params || {};
      that.params.path = result.path;
      that.params.mime = result.mime;
      that.params.copyright = that.copyright;

      // Uploaded new original image
      if (that.isOriginalImage) {
        that.isOriginalImage = false;
        delete that.params.originalImage;
      }

      that.params.width = result.width;
      that.params.height = result.height;

      that.setValue(that.field, that.params);

      for (var i = 0; i < that.changes.length; i++) {
        that.changes[i](that.params);
      }

      // Show edit image button
      that.$editImage.removeClass('hidden');
      that.isEditing = false;
    }
    catch (error) {
      that.$errors.append(ns.createError(error));
    }

    that.addFile();
  };
};

/**
 * Remove image
 */
ns.widgets.image.prototype.removeImage = function () {

  // Notify listeners that we removed image with params
  this.trigger('removedImage', this.params);

  delete this.params;
  this.setValue(this.field);
  this.addFile();

  for (var i = 0; i < this.changes.length; i++) {
    this.changes[i]();
  }
};

/**
 * Replace image with throbber to show that image is being uploaded
 */
ns.widgets.image.prototype.setUploadingThrobber = function () {
  var that = this;

  ns.File.changeCallback = function () {
    // Hide edit image button
    that.$editImage.addClass('hidden');
    that.$file.html('<div class="h5peditor-uploading h5p-throbber">' + ns.t('core', 'uploading') + '</div>');
  };
};

/**
 * Start a new upload.
 */
ns.widgets.image.prototype.uploadFile = function () {
  var that = this;

  if (ns.File.$file === 0) {
    return; // Wait for our turn :)
  }

  this.$errors.html('');

  this.setUploadingThrobber();
  this.setImageChangeCallback();

  if (this.field.mimes !== undefined) {
    var mimes = '';
    for (var i = 0; i < this.field.mimes.length; i++) {
      if (mimes !== '') {
        mimes += ',';
      }
      mimes += this.field.mimes[i];
    }
    ns.File.$file.attr('accept', mimes);
  }
  else if (this.field.type === 'image') {
    ns.File.$file.attr('accept', 'image/jpeg,image/png,image/gif');
  }

  // Uploading new original image
  that.isOriginalImage = true;

  ns.File.$field.val(JSON.stringify(this.field));
  ns.File.$file.click();
};

/**
 * Validate this item
 */
ns.widgets.image.prototype.validate = function () {
  return true;
};

/**
 * Remove this item.
 */
ns.widgets.image.prototype.remove = function () {
  // TODO: Check what happens when removed during upload.
  this.$file.parent().remove();
};

/**
 * Collect functions to execute once the tree is complete.
 *
 * @param {function} ready
 */
ns.widgets.image.prototype.ready = function (ready) {
  if (this.passReadies) {
    this.parent.ready(ready);
  }
  else {
    ready();
  }
};
