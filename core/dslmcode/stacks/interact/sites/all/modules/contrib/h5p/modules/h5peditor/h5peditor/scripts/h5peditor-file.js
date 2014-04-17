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
  this.field = field;
  this.params = params;
  this.setValue = setValue;

  this.changes = [];
};

/**
 * Append field to the given wrapper.
 *
 * @param {jQuery} $wrapper
 * @returns {undefined}
 */
ns.File.prototype.appendTo = function ($wrapper) {
  ns.File.addIframe();

  var label = '';
  if (this.field.label !== 0) {
    label = '<span class="h5peditor-label">' + (this.field.label === undefined ? this.field.name : this.field.label) + '</span>';
  }

  var html = ns.createItem(this.field.type, label + '<div class="file"></div>', this.field.description);

  this.$file = ns.$(html).appendTo($wrapper).children('.file');
  this.addFile();
  this.$errors = this.$file.next();
};

/**
 * Creates thumbnail HTML and actions.
 *
 * @returns {Boolean}
 */
ns.File.prototype.addFile = function () {
  var that = this;

  if (this.params === undefined) {
    this.$file.html('<a href="#" class="add" title="' + ns.t('core', 'addFile') + '"></a>').children('.add').click(function () {
      that.uploadFile();
      return false;
    });
    return;
  }

  var thumbnail;
  if (this.field.type === 'image') {
    thumbnail = {};
    thumbnail.path = H5P.getPath(this.params.path, H5PEditor.contentId),
    thumbnail.height = 100;
    if (this.params.width !== undefined) {
      thumbnail.width = thumbnail.height * (this.params.width / this.params.height);
    }
  }
  else {
    thumbnail = ns.fileIcon;
  }

  this.$file.html('<a href="#" title="' + ns.t('core', 'changeFile') + '" class="thumbnail"><img ' + (thumbnail.width === undefined ? '' : ' width="' + thumbnail.width + '"') + 'height="' + thumbnail.height + '" alt="' + (this.field.label === undefined ? '' : this.field.label) + '"/><a href="#" class="remove" title="' + ns.t('core', 'removeFile') + '"></a></a>').children(':eq(0)').click(function () {
    that.uploadFile();
    return false;
  }).children('img').attr('src', thumbnail.path).end().next().click(function (e) {
    if (!confirm(ns.t('core', 'confirmRemoval', {':type': 'file'}))) {
      return false;
    }
    delete that.params;
    that.setValue(that.field);
    that.addFile();

    for (var i = 0; i < that.changes.length; i++) {
      that.changes[i]();
    }

    return false;
  });
};

/**
 * Start a new upload.
 */
ns.File.prototype.uploadFile = function () {
  var that = this;

  if (ns.File.$file === 0) {
    return; // Wait for our turn :)
  }

  this.$errors.html('');

  ns.File.changeCallback = function () {
    that.$file.html('<div class="h5peditor-uploading">Uploading, please wait...</div>');
  };

  ns.File.callback = function (json) {
    try {
      var result = JSON.parse(json);
      if (result['error'] !== undefined) {
        throw(result['error']);
      }

      that.params = {
        path: result.path,
        mime: result.mime
      };
      if (that.field.type === 'image') {
        that.params.width = result.width;
        that.params.height = result.height;
      }

      that.setValue(that.field, that.params);

      for (var i = 0; i < that.changes.length; i++) {
        that.changes[i](that.params);
      }
    }
    catch (error) {
      that.$errors.append(ns.createError(error));
    }

    that.addFile();
  };

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

  ns.File.$field.val(JSON.stringify(this.field));
  ns.File.$file.click();
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
 * Add the iframe we use for uploads.
 */
ns.File.addIframe = function () {
  if (ns.File.iframeLoaded !== undefined) {
    return;
  }
  ns.File.iframeLoaded = true;

  // All editor uploads share this iframe to conserve valuable resources.
  ns.$('<iframe id="h5peditor-uploader"></iframe>').load(function () {
    var $body = ns.$(this).contents().find('body');
    var json = $body.text();
    if (ns.File.callback !== undefined) {
      ns.File.callback(json);
    }

    $body.html('');
    var $form = ns.$('<form method="post" enctype="multipart/form-data" action="' + ns.ajaxPath + 'files"><input name="file" type="file"/><input name="field" type="hidden"/><input name="contentId" type="hidden" value="' + (ns.contentId === undefined ? 0 : ns.contentId) + '"/></form>').appendTo($body);

    ns.File.$field = $form.children('input[name="field"]');
    ns.File.$file = $form.children('input[name="file"]');

    ns.File.$file.change(function () {
      if (ns.File.changeCallback !== undefined) {
        ns.File.changeCallback();
      }
      ns.File.$field = 0;
      ns.File.$file = 0;
      $form.submit();
    });

  }).appendTo('body');
};

// Tell the editor what widget we are.
ns.widgets.file = ns.File;
ns.widgets.image = ns.File;